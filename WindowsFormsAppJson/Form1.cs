using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MyDLL;

namespace WindowsFormsAppJson
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            if (openFile.ShowDialog() == DialogResult.OK)
            {
                Json json = new Json(openFile.FileName.ToString());
                richTextBox1.AcceptsTab = true;
                richTextBox1.Text = json.test();
                //richTextBox1.Text = File.ReadAllText(openFile.FileName);
                //richTextBox1.Text = ;

            }
        }
    }
}
