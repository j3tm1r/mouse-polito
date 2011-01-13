using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Mouse
{
    using System.Runtime.InteropServices;
    public partial class Form1 : Form
    {
        [DllImport("Dll.dll")]
        public static extern void ApplicaOnMouse(bool c, int v, int s1, int s2, int s3);
        [DllImport("Dll.dll")]
        public static extern void AskMouse(ref bool c, ref int v, ref int s1, ref int s2, ref int s3);
        [DllImport("Dll.dll")]
        public static extern bool check();


        public Form1()
        {
            InitializeComponent();
            startValues();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            //deve attivare il pulsante Applica
            button3.Enabled = true;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void maskedTextBox1_MouseClick(object sender, MouseEventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void statusStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            //deve attivare il pulsante Applica
            button3.Enabled = true;
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void aboutToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Applicazione sviluppata da:\n * Antenucci Danilo\n * Busso Fabio\n * Cerrato Ivano\n * Xhembulla Jetmir");
        }

        private void button2_Click(object sender, EventArgs e)
        {   //Button: Annulla
            Application.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {   //Button: Ok
            if (button3.Enabled) //se è disabilitato, vuol dire che non sono state fatte modifiche
                applica();
            Application.Exit();
        }

        private void button3_Click(object sender, EventArgs e)
        {   //Button: Applica
            applica();
            button3.Enabled = false;
        }

        private void applica()
        {
            //devo vedere se è checked o no
            bool check = false;
            if (checkBox1.Checked)
                check = true;
            //devo prendere il valore della sbarra
            int bar = trackBar1.Value;
            int s1 = trackBar2.Value;
            int s2 = trackBar3.Value;
            int s3 = trackBar4.Value;
            //Chiama la funzione non gestita
            ApplicaOnMouse(check, bar,s1, s2, s3);
            MessageBox.Show("Chek: " + check + " bar: " + bar);
        }

        private void startValues()
        {
            
            button5.Enabled = false;
            button6.Enabled = false;
        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label17_Click(object sender, EventArgs e)
        {

        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            //deve attivare il pulsante Applica
            button3.Enabled = true;
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            //deve attivare il pulsante Applica
            button3.Enabled = true;
        }

        private void trackBar4_Scroll(object sender, EventArgs e)
        {
            //deve attivare il pulsante Applica
            button3.Enabled = true;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            bool check = false;
            if (checkBox1.Checked)
                check = true;
            //devo prendere il valore della sbarra
            int bar = trackBar1.Value;
            int s1 = trackBar2.Value;
            int s2 = trackBar3.Value;
            int s3 = trackBar4.Value;
            //Chiama la funzione non gestita
            ApplicaOnMouse(check, bar, s1, s2, s3);
            label20.Text = "Report inviato";
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (check())
            {
                label18.Text = "Connesso";
                button5.Enabled = true;
                button6.Enabled = true;
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            bool check = false;
            int bar = 0;
            int s1 = 0, s2 = 0, s3 = 0;
            //chiama la funzione non gestita
            //se il mouse non è collegato, l'applicazione termina
              AskMouse(ref check, ref bar, ref s1, ref s2, ref s3);
              
              label19.Text = "Report ricevuto";
        }
    }
}
