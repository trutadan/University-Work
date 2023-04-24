using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using System.Configuration;

namespace laboratory02
{
    public partial class Form1 : Form
    {
        private SqlConnection databaseConnection;
        private SqlDataAdapter parentDataAdapter, childDataAdapter;
        private DataSet tableData;
        private DataRelation parentChildDataRelation;
        private BindingSource parentBindingSource, childBindingSource;

        public Form1()
        {
            InitializeComponent();
        }

        private string getConnectionString()
        {
            return ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString.ToString();
        }

        private string getDatabase()
        {
            return ConfigurationManager.AppSettings["Database"].ToString();
        }

        private string getParentTableName()
        {
            return ConfigurationManager.AppSettings["ParentTableName"].ToString();
        }

        private string getChildTableName()
        {
            return ConfigurationManager.AppSettings["ChildTableName"].ToString();
        }

        private string getParentSelectQuery()
        {
            return "SELECT * FROM " + this.getParentTableName();
        }

        private string getChildSelectQuery()
        {
            return "SELECT * FROM " + this.getChildTableName();
        }

        private string getParentReferencedKey()
        {
            return ConfigurationManager.AppSettings["ParentReferencedKey"].ToString();
        }

        private string getChildForeignKey()
        {
            return ConfigurationManager.AppSettings["ChildForeignKey"].ToString();
        }

        private string getParentSelectionQuery()
        {
            return "SELECT * FROM " + this.getChildTableName() + " WHERE " + this.getChildForeignKey() + " = {0}";

        }

        private void parentTableView_SelectionChanged(object sender, EventArgs e)
        {
            if (parentTableView.SelectedRows.Count != 0)
            {
                DataGridViewRow selectedRow = parentTableView.SelectedRows[0];
                string selectCommandString = String.Format(this.getParentSelectionQuery(), selectedRow.Cells[0].Value);
                childDataAdapter.SelectCommand = new SqlCommand(selectCommandString, databaseConnection);
                this.ReloadChildTableView();
            }
        }

        private void childTableView_DataError(object sender, DataGridViewDataErrorEventArgs error)
        {
            if (error.Exception is InvalidConstraintException)
                MessageBox.Show("The parent id you provided does not exist!");
            else if (error.Exception is FormatException)
                MessageBox.Show(error.Exception.Message);
            else
                try
                {
                    throw error.Exception;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            SqlCommandBuilder builder = new SqlCommandBuilder(childDataAdapter);

            childDataAdapter.UpdateCommand = builder.GetUpdateCommand();
            childDataAdapter.InsertCommand = builder.GetInsertCommand();
            childDataAdapter.DeleteCommand = builder.GetDeleteCommand();

            try
            {
                childDataAdapter.Update(tableData, getChildTableName());
            }
            catch (SqlException sqlException)
            {
                if (sqlException.Number == 2627)
                    MessageBox.Show("There is column data that should be unique in the table!");
                else if (sqlException.Number == 547)
                    MessageBox.Show("There's no parent with the given id!");
                else
                    MessageBox.Show(sqlException.Message);
            }

            this.ReloadChildTableView();
        }

        private void ReloadChildTableView()
        {
            if (tableData.Tables[getChildTableName()] != null)
            {
                tableData.Tables[getChildTableName()].Clear();
            }
            childDataAdapter.Fill(tableData, getChildTableName());
            childTableView.DataSource = childBindingSource;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            databaseConnection = new SqlConnection(String.Format(this.getConnectionString(), this.getDatabase()));
            databaseConnection.Open();

            tableData = new DataSet();

            parentDataAdapter = new SqlDataAdapter(this.getParentSelectQuery(), databaseConnection);
            parentDataAdapter.Fill(tableData, this.getParentTableName());
            parentTableView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            childDataAdapter = new SqlDataAdapter(this.getChildSelectQuery(), databaseConnection);
            childDataAdapter.Fill(tableData, this.getChildTableName());
            childTableView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            DataColumn referenceId = tableData.Tables[this.getParentTableName()].Columns[this.getParentReferencedKey()];
            DataColumn foreignId = tableData.Tables[this.getChildTableName()].Columns[this.getChildForeignKey()];
            parentChildDataRelation = new DataRelation("FK_Parent_Child", referenceId, foreignId);
            tableData.Relations.Add(parentChildDataRelation);

            parentBindingSource = new BindingSource();
            parentBindingSource.DataSource = tableData;
            parentBindingSource.DataMember = this.getParentTableName();

            childBindingSource = new BindingSource();
            childBindingSource.DataSource = parentBindingSource;
            childBindingSource.DataMember = "FK_Parent_Child";

            parentTableView.DataSource = parentBindingSource;
        }
    }
}
