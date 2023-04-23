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
        Json json = new Json();
        string dirToFile = "";

        public Form1()
        {
            InitializeComponent();

            richTextBox1.KeyDown += RichTextBox1_KeyDown;
            richTextBox1.ReadOnly = true;
            richTextBox1.BackColor = Color.White;

            richTextBox2.ReadOnly = true;
            richTextBox3.ReadOnly = true;
        }

        private void RichTextBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Down)
            {
                json.go_down();
                richTextBox1.Text = json.getString();
            }
            else if (e.KeyCode == Keys.Up)
            {
                json.go_up();
                richTextBox1.Text = json.getString();
            }
            else if (e.KeyCode == Keys.Right)
            {
                json.go_in();
                richTextBox1.Text = json.getString();
            }
            else if (e.KeyCode == Keys.Left)
            {
                json.go_out();
                richTextBox1.Text = json.getString();
            }
        }

        private void button1_Click(object sender, EventArgs e) // open
        {
            //richTextBox1.Text = richTextBox3.BackColor.ToString();
            OpenFileDialog openFile = new OpenFileDialog();
            if (openFile.ShowDialog() == DialogResult.OK)
            {
                dirToFile = openFile.FileName.ToString();
                json.load(dirToFile);
                richTextBox1.Text = json.getString();
            }
        }

        private void button2_Click(object sender, EventArgs e) // dell current el
        {
            json.del();
            richTextBox1.Text = json.getString();
        }

        private void button3_Click(object sender, EventArgs e) // save to file
        {
            if (dirToFile != "")
            {
                json.saveToFile(dirToFile);
            }
        }

        private void button4_Click(object sender, EventArgs e) // Edit
        {
            if (dirToFile != "")
            {
                richTextBox3.ReadOnly = false;
                richTextBox3.BackColor = Color.White;
            }
        }

        private void button5_Click(object sender, EventArgs e) // Add new
        { 
            if (dirToFile != "")
            {
                richTextBox2.ReadOnly = false;
                richTextBox2.BackColor = Color.White;
                richTextBox3.ReadOnly = false;
                richTextBox3.BackColor = Color.White;
            }
        }

        private void button6_Click(object sender, EventArgs e) // Approve
        {
            if (dirToFile != "")
            {
                if (richTextBox2.Text == "" && richTextBox3.Text != "")
                {
                    json.setVal(richTextBox3.Text);
                }
                else if (richTextBox2.Text != "" && richTextBox3.Text != "")
                {
                    json.addVal(richTextBox2.Text, richTextBox3.Text);
                }

                richTextBox2.Text = "";
                richTextBox2.ReadOnly = true;
                richTextBox2.BackColor = SystemColors.Control;

                richTextBox3.Text = "";
                richTextBox3.ReadOnly = true;
                richTextBox3.BackColor = SystemColors.Control;

                richTextBox1.Text = json.getString();
            }
        }

        private void button7_Click(object sender, EventArgs e) // Cancel
        {
            richTextBox2.Text = "";
            richTextBox2.ReadOnly = true;
            richTextBox2.BackColor = SystemColors.Control;

            richTextBox3.Text = "";
            richTextBox3.ReadOnly = true;
            richTextBox3.BackColor = SystemColors.Control;
        }
    }

}
