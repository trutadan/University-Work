using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace db_lab01
{
    public partial class Form1 : Form
    {
        private SqlConnection databaseConnection;
        private SqlDataAdapter bandAdapter, albumAdapter;
        private DataSet tableData;
        private DataRelation bandAlbumRelation;
        BindingSource bandBinding, albumBinding;

        public Form1()
        {
            InitializeComponent();
        }

        private void PopulateAlbumTableView()
        {
            // check if the tableData contains a DataTable called RapBandAlbums
            // clear it if it exists
            if (tableData.Tables["RapBandAlbums"] != null)
                tableData.Tables["RapBandAlbums"].Clear();

            // use the albumAdapter to fill the RapBandAlbums DataTable in the tableData with data from the database
            albumAdapter.Fill(tableData, "RapBandAlbums");

            // set the DataSource property of the AlbumGridView to albumBinding that is bound to the RapBandAlbums
            AlbumGridView.DataSource = albumBinding;
        }

        private void BandGridView_SelectionChanged(object sender, EventArgs e)
        {
            // clear the values of album's TextBoxes
            albumIDTextBox.Clear();
            bandIDFromAlbumsTextBox.Clear();
            durationTextBox.Clear();
            numberOfSongsTextBox.Clear();
            titleTextBox.Clear();
            releaseDateTextBox.Clear();

            // check if there is a selected row in the BandGridView control
            if (BandGridView.SelectedRows.Count != 0) {
                // get the selected row
                DataGridViewRow selectedRow = BandGridView.SelectedRows[0];

                // extract the values of the cells in the selected row
                bandIDTextBox.Text = selectedRow.Cells[0].Value.ToString();
                bandNameTextBox.Text = selectedRow.Cells[1].Value.ToString();
                foundationDateTextBox.Text = selectedRow.Cells[2].Value.ToString();
                breakupDateTextBox.Text = selectedRow.Cells[3].Value.ToString();

                // SELECT query that retrieves all albums by the selected band
                string selectQuery = "SELECT * FROM RapBandAlbums WHERE bandID = ";
                albumAdapter.SelectCommand = new SqlCommand(selectQuery + selectedRow.Cells[0].Value, databaseConnection);

                // display the resulting data in another DataGridView
                PopulateAlbumTableView();
            }
        }
        private void AlbumGridView_SelectionChanged(object sender, EventArgs e)
        {
            // check if there is a selected row in the AlbumGridView
            if (AlbumGridView.SelectedRows.Count != 0) {
                // get the selected row
                DataGridViewRow selectedRow = AlbumGridView.SelectedRows[0];

                // extract the values of the cells in the selected row
                albumIDTextBox.Text = selectedRow.Cells[0].Value.ToString();
                bandIDFromAlbumsTextBox.Text = selectedRow.Cells[1].Value.ToString();
                titleTextBox.Text = selectedRow.Cells[2].Value.ToString();
                durationTextBox.Text = selectedRow.Cells[3].Value.ToString();
                numberOfSongsTextBox.Text = selectedRow.Cells[4].Value.ToString();
                releaseDateTextBox.Text = selectedRow.Cells[5].Value.ToString();
            }
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            // SQL query to insert new album data into the database
            string addQuery = "INSERT INTO RapBandAlbums (albumID, bandID, title, duration, numberOfSongs, releaseDate) " +
                "VALUES (@AlbumID, @BandID, @Title, @Duration, @NumberOfSongs, @ReleaseDate)";

            // create SQL command with the insert query and the database connection
            SqlCommand command = new SqlCommand(addQuery, databaseConnection);

            // chekc if an album ID has been entered
            if (albumIDTextBox.Text.Length != 0)
            {
                try {
                    // convert the album ID to an integer
                    int albumID = Int32.Parse(albumIDTextBox.Text);

                    // check if a band ID has been entered
                    if (bandIDFromAlbumsTextBox.Text.Length != 0) {
                        // convert the band ID to an integer
                        int bandID = Int32.Parse(bandIDFromAlbumsTextBox.Text);

                        // initialize the number of songs to 0 if the value is not provided
                        // since it has NOT NULL constraint in the database
                        int numberOfSongs;
                        if (numberOfSongsTextBox.Text.Length != 0)
                            numberOfSongs = Int32.Parse(numberOfSongsTextBox.Text);
                        else
                            numberOfSongs = 0;

                        // add parameters to the SQL command object
                        command.Parameters.Add("@AlbumID", SqlDbType.Int);
                        command.Parameters["@AlbumID"].Value = albumID;

                        command.Parameters.Add("@BandID", SqlDbType.Int);
                        command.Parameters["@BandID"].Value = bandID;

                        command.Parameters.Add("@Title", SqlDbType.VarChar, 50);
                        command.Parameters["@Title"].Value = titleTextBox.Text;

                        command.Parameters.Add("@Duration", SqlDbType.VarChar, 10);
                        command.Parameters["@Duration"].Value = durationTextBox.Text;

                        command.Parameters.Add("@NumberOfSongs", SqlDbType.VarChar, 10);
                        command.Parameters["@NumberOfSongs"].Value = numberOfSongs;

                        command.Parameters.Add("@ReleaseDate", SqlDbType.VarChar, 30);
                        command.Parameters["@ReleaseDate"].Value = releaseDateTextBox.Text;

                        try {
                            // set the insert command for the album adapter to the SQL command object
                            albumAdapter.InsertCommand = command;

                            // execute the insert command
                            albumAdapter.InsertCommand.ExecuteNonQuery();

                            // repopulate the album table view with the updated data
                            PopulateAlbumTableView();
                        } catch (SqlException sqlException) {
                            // primary key exception
                            if (sqlException.Number == 2627)
                                MessageBox.Show("The album id must be unique!");
                            // foreign key exception
                            else if (sqlException.Number == 547)
                                MessageBox.Show("No band was found for the given id!");
                            else
                                MessageBox.Show(sqlException.Message);
                        }
                    }
                    else
                        MessageBox.Show("Please provide a band id!");
                } catch (FormatException ex) {
                    MessageBox.Show(ex.Message);
                }
            }
            else
                MessageBox.Show("Please provide an album id!");
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            // SqlCommand with a parameterized query to delete an album from the database
            SqlCommand command = new SqlCommand("DELETE FROM RapBandAlbums WHERE albumID = @AlbumID", databaseConnection);

            // check if the albumIDTextBox has a value entered
            if (albumIDTextBox.Text.Length != 0) {
                // convert the text entered in the albumIDTextBox to an integer
                int albumID = Int32.Parse(albumIDTextBox.Text);

                // add a parameter to the SqlCommand object for the albumID value
                command.Parameters.Add("@AlbumID", SqlDbType.Int);
                command.Parameters["@AlbumID"].Value = albumID;

                try {
                    // set the DeleteCommand property of the SqlDataAdapter to the SqlCommand created above
                    albumAdapter.DeleteCommand = command;

                    // execute the DELETE query and get the number of albums deleted
                    int numberOfDeletedAlbums = albumAdapter.DeleteCommand.ExecuteNonQuery();

                    if (numberOfDeletedAlbums == 0)
                        MessageBox.Show("No album found for the given id!");
                    else
                        PopulateAlbumTableView();
                } catch (SqlException sqlException) {
                    MessageBox.Show(sqlException.ToString());
                }
            }
            else
                MessageBox.Show("Please provide an id for the album!");
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            SqlCommandBuilder builder = new SqlCommandBuilder(albumAdapter);

            // allow changes made to the dataset to be automatically updated in the database
            albumAdapter.UpdateCommand = builder.GetUpdateCommand();
            
            try {
                albumAdapter.Update(tableData, "RapBandAlbums");
            } catch (SqlException sqlException) {
                if (sqlException.Number == 2627)
                    MessageBox.Show("Album ID must be unique!");
                else if (sqlException.Number == 547)
                    MessageBox.Show("No rap band found for the given id!");
                else
                    MessageBox.Show(sqlException.Message);
            }

            // refresh the album table view in the user interface to reflect any changes made to the data
            PopulateAlbumTableView();
        }

        string getConnectionString()
        {
            // get the connection string used to connect to the database
            return "Server=DESKTOP-3SQEJ2L\\SQLEXPRESS;Database=Rap;Trusted_Connection=true;";
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // establish a connection to the database
            databaseConnection = new SqlConnection(getConnectionString());
            databaseConnection.Open();

            // query the RapBands table and fill a DataSet with the results
            string queryRapBands = "SELECT * FROM RapBands";
            bandAdapter = new SqlDataAdapter(queryRapBands, databaseConnection);
            tableData = new DataSet();
            bandAdapter.Fill(tableData, "RapBands");

            // set the selection mode of the BandGridView to full row select
            BandGridView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            // query the RapBandAlbums table and fill the DataSet with the results
            string queryRapBandAlbums = "SELECT * FROM RapBandAlbums";
            albumAdapter = new SqlDataAdapter(queryRapBandAlbums, databaseConnection);
            albumAdapter.Fill(tableData, "RapBandAlbums");

            // set the selection mode of the AlbumGridView to full row select
            AlbumGridView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            // set up the relationship between the RapBands and RapBandAlbums tables
            DataColumn bandID = tableData.Tables["RapBands"].Columns["bandID"];
            DataColumn albumBandID = tableData.Tables["RapBandAlbums"].Columns["bandID"];
            bandAlbumRelation = new DataRelation("FK_BAND_ALBUM", bandID, albumBandID);
            tableData.Relations.Add(bandAlbumRelation);

            // Set up the data bindings for the BandGridView and AlbumGridView
            bandBinding = new BindingSource();
            bandBinding.DataSource = tableData;
            bandBinding.DataMember = "RapBands";

            albumBinding = new BindingSource();
            albumBinding.DataSource = bandBinding;
            albumBinding.DataMember = "FK_BAND_ALBUM";

            BandGridView.DataSource = bandBinding;
        }
    }
}
