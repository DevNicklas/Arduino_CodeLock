using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.IO;

namespace Arduino_CodeLock
{
    internal class Program
    {
        static void Main(string[] args)
        {
            const string COM_PORT = "COM5";
            const int BAUD_RATE = 9600;

            SerialPort sp = new SerialPort(COM_PORT, BAUD_RATE);
            sp.DataReceived += new SerialDataReceivedEventHandler(SerialPortDataReceived);

            sp.Open();
            Console.WriteLine("Listening on port: " + sp.PortName);
            Console.ReadKey();
            sp.Close();
        }

        private static void SerialPortDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string data = sp.ReadLine();

            Console.WriteLine("Received data: " + data);
            WriteToFile(data);
        }

        private static void WriteToFile(string data)
        {
            using(StreamWriter sw = new StreamWriter("Codelock_Data.txt", true))
            {
                sw.WriteLine(data + ", test");
            }
        }

    }
}
