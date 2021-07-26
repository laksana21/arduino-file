using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;
using System.Windows.Forms;
using System.IO.Ports;

namespace SmartHomeController
{
    public partial class RemoteControl : Form
    {
        string line;
        SerialPort serial = new SerialPort();
        int lampu = 0;
        int kipas = 0;
        int pompa = 0;

        public RemoteControl()
        {
            InitializeComponent();
            PerintahUtama();
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            line = serial.ReadLine();
            this.BeginInvoke(new LineReceivedEvent(LineReceived), line);
        }

        private delegate void LineReceivedEvent(string line);
        private void LineReceived(string line)
        {
            //What to do with the received line here
            lbHum.Text = Convert.ToString(line[0]);
            lbHum.Text += Convert.ToString(line[1]);

            lbMois.Text = Convert.ToString(line[9]);
            lbMois.Text += Convert.ToString(line[10]);
            lbMois.Text += Convert.ToString(line[11]);

            lbTemp.Text = Convert.ToString(line[5]);
            lbTemp.Text += Convert.ToString(line[6]);

            string strStream = Convert.ToString(line[13]);
            strStream += Convert.ToString(line[14]);

            pbDataStream.Value = int.Parse(strStream);

            try
            {
                int mois = Convert.ToInt32(lbMois.Text);
                int hum = Convert.ToInt32(lbHum.Text);
                int temp = Convert.ToInt32(lbTemp.Text);
                CheckKondisi(mois, hum, temp);

                var conn = new MySqlConnection("Host=localhost;Uid=root;Pwd=;Database=dbsmartgh");
                var cmd = new MySqlCommand("UPDATE `tbkondisi` SET `SoilMoisture`=" + mois + ",`AirHumidity`=" + hum + ",`AirTemp`=" + temp + " WHERE `NoData` = 0 ", conn);
                conn.Open();
                cmd.ExecuteReader();

                CheckPerintah();
                PerintahUtama();
                if (lampu == 1 && pompa == 0 && kipas == 0)
                { serial.Write("A"); }
                else if (lampu == 0 && pompa == 1 && kipas == 0)
                { serial.Write("B"); }
                else if (lampu == 0 && pompa == 0 && kipas == 1)
                { serial.Write("C"); }
                else if (lampu == 1 && pompa == 1 && kipas == 0)
                { serial.Write("D"); }
                else if (lampu == 1 && pompa == 0 && kipas == 1)
                { serial.Write("E"); }
                else if (lampu == 0 && pompa == 1 && kipas == 1)
                { serial.Write("F"); }
                else if (lampu == 1 && pompa == 1 && kipas == 1)
                { serial.Write("G"); }
                else
                { serial.Write("X"); }

                conn.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void RemoteControl_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            string port = Convert.ToString(cbPort.Text);
            int baud = Convert.ToInt32(cbBaud.Text);

            if (chkDtr.Checked == true)
            {
                serial.DtrEnable = true;
            }
            else
            {
                serial.DtrEnable = false;
            }
            
            serial.PortName = port;
            serial.BaudRate = baud;
            serial.Open();

            serial.DataReceived += serialPort1_DataReceived;
        }
        private void CheckPerintah()
        {
            if (chkLampu.Checked == true)
            {
                lampu = 1;
            }
            else
            {
                lampu = 0;
            }
            if (chkPompa.Checked == true)
            {
                pompa = 1;
            }
            else
            {
                pompa = 0;
            }
            if (chkKipas.Checked == true)
            {
                kipas = 1;
            }
            else
            {
                kipas = 0;
            }

            try
            {
                var conn = new MySqlConnection("Host=localhost;Uid=root;Pwd=;Database=dbsmartgh");
                var cmd = new MySqlCommand("UPDATE `tbperintah` SET `Lampu`=" + lampu + ",`Pompa`=" + pompa + ",`Kipas`=" + kipas + " WHERE `NoPerintah` = 0 ", conn);
                conn.Open();
                cmd.ExecuteReader();
                conn.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void CheckKondisi(int mois, int hum, int temp)
        {
            int m = mois;
            int h = hum;
            int t = temp;

            if (m >= 80)
            { lbStatus.Text = "Kurang Air"; }
            else if (m <= 40)
            { lbStatus.Text = "Kelebihan \nAir"; }
            else if (t >= 60)
            { lbStatus.Text = "Udara Panas"; }
            else if (t <= 1)
            { lbStatus.Text = "Udara Dingin"; }
            else if (h >= 90 || h <= 20)
            { lbStatus.Text = "Udara tidak \nAman"; }
            else
            { lbStatus.Text = "Aman \nTerkendali"; }
        }
        private void PerintahUtama()
        {
            try
            {
                var conn = new MySqlConnection("Host=localhost;Uid=root;Pwd=;Database=dbsmartgh");
                var cmd = new MySqlCommand("SELECT * FROM `tbperintah` WHERE `NoPerintah` = '0'", conn);
                conn.Open();
                var r = cmd.ExecuteReader();
                r.Read();

                lampu = Convert.ToInt32(r[1]);
                pompa = Convert.ToInt32(r[2]);
                kipas = Convert.ToInt32(r[3]);

                if (lampu > 0)
                {
                    chkLampu.Checked = true;
                }
                if (pompa > 0)
                {
                    chkPompa.Checked = true;
                }
                if (kipas > 0)
                {
                    chkKipas.Checked = true;
                }
                conn.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
