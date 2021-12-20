using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Threading;
using System.Text;
using System.Net.Sockets;
using System;
using System.Net;
using System.IO.Compression;

public class SimpleTcpClient
{
    public void Connect()
    {

    }
}
public class UpdateController : MonoBehaviour
{
    public static bool isChristmas = false;
    public static bool isNewLvl = false;
    public static bool isAuto = false;
    public static string VersionStr;
    public GameObject checkUpdates;
    public GameObject updateProgress;
    public GameObject updateComplete;
    public Text updateProgressText;
    public Text CheckUpdateVersion;
    public Text Version;
    public Text description;
    public GameObject updateNotFound;
    public Toggle toggle;
    bool isConnected = false;

    bool isUpdating = false;
    private string pathUpdateAvailable = "D:\\UpdateInfo\\UpdateAvailable.txt";
    private string pathUpdateInfo = "D:\\UpdateInfo\\UpdateInfo.txt";
    private string pathCurrentVersion = "D:\\UpdateInfo\\CurrentVersion.txt";
    private void Awake()
    {
        using(StreamReader sr = new StreamReader(pathCurrentVersion))
        {
            string result = sr.ReadToEnd();
            if(result[0] == '1')
                isChristmas = true;
            else if(result[0] == '0')
                isChristmas = false;

            if(result[1] == '1')
                isNewLvl = true;
            else if(result[1] == '0')
                isNewLvl = false;
            
            VersionStr = result.Substring(2);
            Version.text = VersionStr;
        }
    }
    private void Start()
    {
        // StartCoroutine(ExampleCoroutine());
    }
    private void Update()
    {
        string result;
        using(StreamReader sr = new StreamReader(pathUpdateAvailable))
        {
            result = sr.ReadToEnd();
        }
        if(result == "1" && isAuto)
        {
            StartCoroutine(ExampleCoroutine());
            AutoUpdate();
            result = string.Empty;           
        }
    }
    public IEnumerator ExampleCoroutine()
    {
        yield return new WaitForSeconds(4);
        updateProgress.SetActive(true);
        updateProgressText.text = "Loading: christmas.txt";
        yield return new WaitForSeconds(0.5f);
        updateProgressText.text = "Loading: Helper.dll";
        yield return new WaitForSeconds(0.5f);
        updateProgressText.text = "Loading: video.mp4";
        yield return new WaitForSeconds(1);
        updateProgress.SetActive(false);
        updateComplete.SetActive(true);
        yield return new WaitForSeconds(5);
        SceneManager.LoadScene(0);
    }
    public void AutoUpdate()
    {
        
        string current = string.Empty;
        using(StreamReader sr = new StreamReader(pathUpdateInfo))
        {
            string result = sr.ReadLine();
            current = result.Substring(0, result.Length - (result.Length - 7));
            if(result[0] == '1')
            {
                isChristmas = true;
            }
            else if(result[0] == '0')
                isChristmas = false;

            if(result[1] == '1')
            {
                isNewLvl = true;
            }
            else if(result[1] == '0')
                isNewLvl = false; 
            
            // updateProgressText.text = "Loading: christmas.txt";
            // yield return new WaitForSeconds(5);
            // updateProgressText.text = "Loading: Helper.dll";
            // yield return new WaitForSeconds(5);
            // updateProgressText.text = "Loading: video.mp4";
        }
        using(StreamWriter sw = new StreamWriter(pathUpdateAvailable, false, System.Text.Encoding.Default))
        {
            sw.Write('0');
        }
        using(StreamWriter sw = new StreamWriter(pathCurrentVersion, false, System.Text.Encoding.Default))
        {
            sw.Write(current);
        }

    }
    public void TogglePress()
    {
        isAuto = toggle.isOn;
    }
    public void CheckUpdate()
    {
        using(StreamReader sr = new StreamReader(pathUpdateAvailable))
        {
            string result = sr.ReadToEnd();
            if(result == "0")
                updateNotFound.SetActive(true);
            else if(result == "1")
            {
                checkUpdates.SetActive(true);
                using(StreamReader sr1 = new StreamReader(pathUpdateInfo))
                {
                    string result1 = sr1.ReadLine();

                    CheckUpdateVersion.text = result1.Substring(2, result1.Length - (result1.Length - 5));
                    description.text = result1.Substring(7);
                }
            }
        }
    }
    public void UpdateButton()
    {
        Thread.Sleep(2000);
        string current = string.Empty;
        using(StreamReader sr = new StreamReader(pathUpdateInfo))
        {
            string result = sr.ReadLine();
            current = result.Substring(0, result.Length - (result.Length - 7));
            if(result[0] == '1')
                isChristmas = true;
            else if(result[0] == '0')
                isChristmas = false;

            if(result[1] == '1')
                isNewLvl = true;
            else if(result[1] == '0')
                isNewLvl = false;
        }
        checkUpdates.SetActive(false);
        using(StreamWriter sw = new StreamWriter(pathUpdateAvailable, false, System.Text.Encoding.Default))
        {
            sw.Write('0');
        }
        // using(StreamWriter sw = new StreamWriter(pathUpdateInfo, false, System.Text.Encoding.Default))
        // {
        //     sw.Write(string.Empty);
        // }
        using(StreamWriter sw = new StreamWriter(pathCurrentVersion, false, System.Text.Encoding.Default))
        {
            sw.Write(current);
        }
        SceneManager.LoadScene(0);
    }

    public SimpleTcpClient client = new SimpleTcpClient();
    public void Connect()
    {
        while(!isConnected)
        try
        {
            client.Connect();
            isConnected = true;
        }
        catch(Exception ex)
        {
            Debug.Log("error"+ex.Message);
        }
    }
    public void ReciveData()
    {
        int Port = 9000;

        TcpListener listener = new TcpListener(IPAddress.Any, Port);
        listener.Start();


        Socket socket = listener.AcceptSocket();

        int bufferSize = 1024;
        byte[] buffer = null;
        byte[] header = null;
        string headerStr = "";
        string filename = "";
        int filesize = 0;


        header = new byte[bufferSize];

        socket.Receive(header);

        headerStr = Encoding.ASCII.GetString(header);


        string[] splitted = headerStr.Split(new string[] { "\r\n" }, StringSplitOptions.None);
        Dictionary<string, string> headers = new Dictionary<string, string>();
        foreach (string s in splitted)
        {
            if (s.Contains(":"))
            {
                headers.Add(s.Substring(0, s.IndexOf(":")), s.Substring(s.IndexOf(":") + 1));
            }

        }
        //Get filesize from header
        filesize = Convert.ToInt32(headers["Content-length"]);
        //Get filename from header
        filename = headers["Filename"];

        int bufferCount = Convert.ToInt32(Math.Ceiling((double)filesize / (double)bufferSize));


        FileStream fs = new FileStream(filename, FileMode.OpenOrCreate);

        while (filesize > 0)
        {
            buffer = new byte[bufferSize];

            int size = socket.Receive(buffer, SocketFlags.Partial);

            fs.Write(buffer, 0, size);

            filesize -= size;
        }

        UnZip();
        fs.Close();
    }
    public void UnZip()
    {
        string zipPath = @"D:\UpdateFrom\Update.zip";
        string extractPath = @"D:\UpdateTo";

        ZipFile.ExtractToDirectory(zipPath, extractPath);
        File.Delete(zipPath);
    }
    public void CloseButton()
    {
        checkUpdates.SetActive(false);
        updateNotFound.SetActive(false);
    }
}
