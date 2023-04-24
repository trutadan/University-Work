namespace db_lab01
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.AlbumGridView = new System.Windows.Forms.DataGridView();
            this.BandGridView = new System.Windows.Forms.DataGridView();
            this.bandLabel = new System.Windows.Forms.Label();
            this.albumLabel = new System.Windows.Forms.Label();
            this.bandIDLabel = new System.Windows.Forms.Label();
            this.bandNameLabel = new System.Windows.Forms.Label();
            this.foundationDateLabel = new System.Windows.Forms.Label();
            this.breakupDateLabel = new System.Windows.Forms.Label();
            this.albumIDLabel = new System.Windows.Forms.Label();
            this.albumsbandIDLabel = new System.Windows.Forms.Label();
            this.titleLabel = new System.Windows.Forms.Label();
            this.durationLabel = new System.Windows.Forms.Label();
            this.numberOfSongsLabel = new System.Windows.Forms.Label();
            this.releaseDateLabel = new System.Windows.Forms.Label();
            this.addButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            this.bandIDTextBox = new System.Windows.Forms.TextBox();
            this.bandNameTextBox = new System.Windows.Forms.TextBox();
            this.foundationDateTextBox = new System.Windows.Forms.TextBox();
            this.breakupDateTextBox = new System.Windows.Forms.TextBox();
            this.albumIDTextBox = new System.Windows.Forms.TextBox();
            this.bandIDFromAlbumsTextBox = new System.Windows.Forms.TextBox();
            this.releaseDateTextBox = new System.Windows.Forms.TextBox();
            this.numberOfSongsTextBox = new System.Windows.Forms.TextBox();
            this.durationTextBox = new System.Windows.Forms.TextBox();
            this.titleTextBox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.AlbumGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.BandGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // AlbumGridView
            // 
            this.AlbumGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.AlbumGridView.Location = new System.Drawing.Point(415, 43);
            this.AlbumGridView.Name = "AlbumGridView";
            this.AlbumGridView.Size = new System.Drawing.Size(373, 210);
            this.AlbumGridView.TabIndex = 0;
            this.AlbumGridView.SelectionChanged += new System.EventHandler(this.AlbumGridView_SelectionChanged);
            // 
            // BandGridView
            // 
            this.BandGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.BandGridView.Location = new System.Drawing.Point(12, 43);
            this.BandGridView.Name = "BandGridView";
            this.BandGridView.Size = new System.Drawing.Size(373, 260);
            this.BandGridView.TabIndex = 1;
            this.BandGridView.SelectionChanged += new System.EventHandler(this.BandGridView_SelectionChanged);
            // 
            // bandLabel
            // 
            this.bandLabel.AutoSize = true;
            this.bandLabel.Location = new System.Drawing.Point(168, 27);
            this.bandLabel.Name = "bandLabel";
            this.bandLabel.Size = new System.Drawing.Size(57, 13);
            this.bandLabel.TabIndex = 2;
            this.bandLabel.Text = "RapBands";
            // 
            // albumLabel
            // 
            this.albumLabel.AutoSize = true;
            this.albumLabel.Location = new System.Drawing.Point(566, 27);
            this.albumLabel.Name = "albumLabel";
            this.albumLabel.Size = new System.Drawing.Size(86, 13);
            this.albumLabel.TabIndex = 3;
            this.albumLabel.Text = "RapBandAlbums";
            // 
            // bandIDLabel
            // 
            this.bandIDLabel.AutoSize = true;
            this.bandIDLabel.Location = new System.Drawing.Point(9, 317);
            this.bandIDLabel.Name = "bandIDLabel";
            this.bandIDLabel.Size = new System.Drawing.Size(42, 13);
            this.bandIDLabel.TabIndex = 27;
            this.bandIDLabel.Text = "bandID";
            // 
            // bandNameLabel
            // 
            this.bandNameLabel.AutoSize = true;
            this.bandNameLabel.Location = new System.Drawing.Point(9, 342);
            this.bandNameLabel.Name = "bandNameLabel";
            this.bandNameLabel.Size = new System.Drawing.Size(59, 13);
            this.bandNameLabel.TabIndex = 28;
            this.bandNameLabel.Text = "bandName";
            // 
            // foundationDateLabel
            // 
            this.foundationDateLabel.AutoSize = true;
            this.foundationDateLabel.Location = new System.Drawing.Point(9, 368);
            this.foundationDateLabel.Name = "foundationDateLabel";
            this.foundationDateLabel.Size = new System.Drawing.Size(80, 13);
            this.foundationDateLabel.TabIndex = 29;
            this.foundationDateLabel.Text = "foundationDate";
            // 
            // breakupDateLabel
            // 
            this.breakupDateLabel.AutoSize = true;
            this.breakupDateLabel.Location = new System.Drawing.Point(9, 394);
            this.breakupDateLabel.Name = "breakupDateLabel";
            this.breakupDateLabel.Size = new System.Drawing.Size(69, 13);
            this.breakupDateLabel.TabIndex = 30;
            this.breakupDateLabel.Text = "breakupDate";
            // 
            // albumIDLabel
            // 
            this.albumIDLabel.AutoSize = true;
            this.albumIDLabel.Location = new System.Drawing.Point(412, 264);
            this.albumIDLabel.Name = "albumIDLabel";
            this.albumIDLabel.Size = new System.Drawing.Size(46, 13);
            this.albumIDLabel.TabIndex = 8;
            this.albumIDLabel.Text = "albumID";
            // 
            // albumsbandIDLabel
            // 
            this.albumsbandIDLabel.AutoSize = true;
            this.albumsbandIDLabel.Location = new System.Drawing.Point(412, 290);
            this.albumsbandIDLabel.Name = "albumsbandIDLabel";
            this.albumsbandIDLabel.Size = new System.Drawing.Size(42, 13);
            this.albumsbandIDLabel.TabIndex = 9;
            this.albumsbandIDLabel.Text = "bandID";
            // 
            // titleLabel
            // 
            this.titleLabel.AutoSize = true;
            this.titleLabel.Location = new System.Drawing.Point(412, 317);
            this.titleLabel.Name = "titleLabel";
            this.titleLabel.Size = new System.Drawing.Size(23, 13);
            this.titleLabel.TabIndex = 10;
            this.titleLabel.Text = "title";
            // 
            // durationLabel
            // 
            this.durationLabel.AutoSize = true;
            this.durationLabel.Location = new System.Drawing.Point(412, 342);
            this.durationLabel.Name = "durationLabel";
            this.durationLabel.Size = new System.Drawing.Size(45, 13);
            this.durationLabel.TabIndex = 11;
            this.durationLabel.Text = "duration";
            // 
            // numberOfSongsLabel
            // 
            this.numberOfSongsLabel.AutoSize = true;
            this.numberOfSongsLabel.Location = new System.Drawing.Point(412, 368);
            this.numberOfSongsLabel.Name = "numberOfSongsLabel";
            this.numberOfSongsLabel.Size = new System.Drawing.Size(83, 13);
            this.numberOfSongsLabel.TabIndex = 12;
            this.numberOfSongsLabel.Text = "numberOfSongs";
            // 
            // releaseDateLabel
            // 
            this.releaseDateLabel.AutoSize = true;
            this.releaseDateLabel.Location = new System.Drawing.Point(412, 394);
            this.releaseDateLabel.Name = "releaseDateLabel";
            this.releaseDateLabel.Size = new System.Drawing.Size(64, 13);
            this.releaseDateLabel.TabIndex = 13;
            this.releaseDateLabel.Text = "releaseDate";
            // 
            // addButton
            // 
            this.addButton.Location = new System.Drawing.Point(150, 417);
            this.addButton.Name = "addButton";
            this.addButton.Size = new System.Drawing.Size(75, 23);
            this.addButton.TabIndex = 14;
            this.addButton.Text = "Add";
            this.addButton.UseVisualStyleBackColor = true;
            this.addButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // deleteButton
            // 
            this.deleteButton.Location = new System.Drawing.Point(360, 417);
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.Size = new System.Drawing.Size(75, 23);
            this.deleteButton.TabIndex = 15;
            this.deleteButton.Text = "Delete";
            this.deleteButton.UseVisualStyleBackColor = true;
            this.deleteButton.Click += new System.EventHandler(this.deleteButton_Click);
            // 
            // updateButton
            // 
            this.updateButton.Location = new System.Drawing.Point(577, 417);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(75, 23);
            this.updateButton.TabIndex = 16;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // bandIDTextBox
            // 
            this.bandIDTextBox.Location = new System.Drawing.Point(57, 314);
            this.bandIDTextBox.Name = "bandIDTextBox";
            this.bandIDTextBox.ReadOnly = true;
            this.bandIDTextBox.Size = new System.Drawing.Size(328, 20);
            this.bandIDTextBox.TabIndex = 31;
            this.bandIDTextBox.ReadOnly = true;
            // 
            // bandNameTextBox
            // 
            this.bandNameTextBox.Location = new System.Drawing.Point(74, 340);
            this.bandNameTextBox.Name = "bandNameTextBox";
            this.bandNameTextBox.ReadOnly = true;
            this.bandNameTextBox.Size = new System.Drawing.Size(311, 20);
            this.bandNameTextBox.TabIndex = 32;
            this.bandNameTextBox.ReadOnly = true;
            // 
            // foundationDateTextBox
            // 
            this.foundationDateTextBox.Location = new System.Drawing.Point(95, 365);
            this.foundationDateTextBox.Name = "foundationDateTextBox";
            this.foundationDateTextBox.ReadOnly = true;
            this.foundationDateTextBox.Size = new System.Drawing.Size(290, 20);
            this.foundationDateTextBox.TabIndex = 33;
            this.foundationDateTextBox.ReadOnly = true;
            // 
            // breakupDateTextBox
            // 
            this.breakupDateTextBox.Location = new System.Drawing.Point(84, 391);
            this.breakupDateTextBox.Name = "breakupDateTextBox";
            this.breakupDateTextBox.ReadOnly = true;
            this.breakupDateTextBox.Size = new System.Drawing.Size(301, 20);
            this.breakupDateTextBox.TabIndex = 34;
            this.breakupDateTextBox.ReadOnly = true;
            // 
            // albumIDTextBox
            // 
            this.albumIDTextBox.Location = new System.Drawing.Point(460, 261);
            this.albumIDTextBox.Name = "albumIDTextBox";
            this.albumIDTextBox.ReadOnly = true;
            this.albumIDTextBox.Size = new System.Drawing.Size(328, 20);
            this.albumIDTextBox.TabIndex = 17;
            // 
            // bandIDFromAlbumsTextBox
            // 
            this.bandIDFromAlbumsTextBox.Location = new System.Drawing.Point(460, 287);
            this.bandIDFromAlbumsTextBox.Name = "bandIDFromAlbumsTextBox";
            this.bandIDFromAlbumsTextBox.ReadOnly = true;
            this.bandIDFromAlbumsTextBox.Size = new System.Drawing.Size(328, 20);
            this.bandIDFromAlbumsTextBox.TabIndex = 22;
            // 
            // releaseDateTextBox
            // 
            this.releaseDateTextBox.Location = new System.Drawing.Point(482, 391);
            this.releaseDateTextBox.Name = "releaseDateTextBox";
            this.releaseDateTextBox.ReadOnly = true;
            this.releaseDateTextBox.Size = new System.Drawing.Size(306, 20);
            this.releaseDateTextBox.TabIndex = 23;
            // 
            // numberOfSongsTextBox
            // 
            this.numberOfSongsTextBox.Location = new System.Drawing.Point(501, 365);
            this.numberOfSongsTextBox.Name = "numberOfSongsTextBox";
            this.numberOfSongsTextBox.ReadOnly = true;
            this.numberOfSongsTextBox.Size = new System.Drawing.Size(287, 20);
            this.numberOfSongsTextBox.TabIndex = 24;
            // 
            // durationTextBox
            // 
            this.durationTextBox.Location = new System.Drawing.Point(460, 339);
            this.durationTextBox.Name = "durationTextBox";
            this.durationTextBox.ReadOnly = true;
            this.durationTextBox.Size = new System.Drawing.Size(328, 20);
            this.durationTextBox.TabIndex = 25;
            // 
            // titleTextBox
            // 
            this.titleTextBox.Location = new System.Drawing.Point(441, 313);
            this.titleTextBox.Name = "titleTextBox";
            this.titleTextBox.ReadOnly = true;
            this.titleTextBox.Size = new System.Drawing.Size(347, 20);
            this.titleTextBox.TabIndex = 26;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.breakupDateTextBox);
            this.Controls.Add(this.foundationDateTextBox);
            this.Controls.Add(this.bandNameTextBox);
            this.Controls.Add(this.bandIDTextBox);
            this.Controls.Add(this.breakupDateLabel);
            this.Controls.Add(this.foundationDateLabel);
            this.Controls.Add(this.bandNameLabel);
            this.Controls.Add(this.bandIDLabel);
            this.Controls.Add(this.titleTextBox);
            this.Controls.Add(this.durationTextBox);
            this.Controls.Add(this.numberOfSongsTextBox);
            this.Controls.Add(this.releaseDateTextBox);
            this.Controls.Add(this.bandIDFromAlbumsTextBox);
            this.Controls.Add(this.albumIDTextBox);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.addButton);
            this.Controls.Add(this.releaseDateLabel);
            this.Controls.Add(this.numberOfSongsLabel);
            this.Controls.Add(this.durationLabel);
            this.Controls.Add(this.titleLabel);
            this.Controls.Add(this.albumsbandIDLabel);
            this.Controls.Add(this.albumIDLabel);
            this.Controls.Add(this.albumLabel);
            this.Controls.Add(this.bandLabel);
            this.Controls.Add(this.BandGridView);
            this.Controls.Add(this.AlbumGridView);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.AlbumGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.BandGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView AlbumGridView;
        private System.Windows.Forms.DataGridView BandGridView;
        private System.Windows.Forms.Label bandLabel;
        private System.Windows.Forms.Label albumLabel;
        private System.Windows.Forms.Label albumIDLabel;
        private System.Windows.Forms.Label albumsbandIDLabel;
        private System.Windows.Forms.Label titleLabel;
        private System.Windows.Forms.Label durationLabel;
        private System.Windows.Forms.Label numberOfSongsLabel;
        private System.Windows.Forms.Label releaseDateLabel;
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.Button deleteButton;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.TextBox albumIDTextBox;
        private System.Windows.Forms.TextBox bandIDFromAlbumsTextBox;
        private System.Windows.Forms.TextBox releaseDateTextBox;
        private System.Windows.Forms.TextBox numberOfSongsTextBox;
        private System.Windows.Forms.TextBox durationTextBox;
        private System.Windows.Forms.TextBox titleTextBox;
        private System.Windows.Forms.Label bandIDLabel;
        private System.Windows.Forms.Label bandNameLabel;
        private System.Windows.Forms.Label foundationDateLabel;
        private System.Windows.Forms.Label breakupDateLabel;
        private System.Windows.Forms.TextBox bandIDTextBox;
        private System.Windows.Forms.TextBox bandNameTextBox;
        private System.Windows.Forms.TextBox foundationDateTextBox;
        private System.Windows.Forms.TextBox breakupDateTextBox;
    }
}

