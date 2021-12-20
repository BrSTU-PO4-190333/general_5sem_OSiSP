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

public class UpdateVersion : MonoBehaviour
{
    public GameObject upd;
    private string result;
    public bool is_AutoUpd = true;
    public GameObject Down;
    public GameObject CompleteMes;
    public Toggle toggle1;
    public Text DownText;

    public static bool isSkiped = false;
    public static bool isNewLvl = false;
    private int timer = 0;



    public IEnumerator Queue()
    {
        yield return new WaitForSeconds(4);
        Down.SetActive(true);
        DownText.text = "Загрузка Меню и логов";
        yield return new WaitForSeconds(1);
        DownText.text = "Загрузка нового уровня";
        yield return new WaitForSeconds(1);
        DownText.text = "Загрузка видео .mp4";
        yield return new WaitForSeconds(2);
        CompleteMes.SetActive(true);
        yield return new WaitForSeconds(5);
        SceneManager.LoadScene(0);
    }



    private void Update()
    {
        
        if (is_AutoUpd == true){
            
            using(StreamReader sr = new StreamReader("D:\\kakho4h.txt"))
            {
                result = sr.ReadToEnd();
                
            }

            if(result == "1")
            {
                StartCoroutine(Queue());
                isNewLvl = true;
                using(StreamWriter sw = new StreamWriter("D:\\kakho4h.txt", false, System.Text.Encoding.Default))
                {
                    sw.Write(0);
                }
                
                
            }
        }
        
    }

    public void TogleBtn(){
        is_AutoUpd = toggle1.isOn;
        Debug.Log(is_AutoUpd);
        
    }

    public void UpdateBtn()
    {
        Time.timeScale = 1f;
        isNewLvl = true;
        using(StreamWriter sw = new StreamWriter("D:\\kakho4h.txt", false, System.Text.Encoding.Default))
        {
            sw.Write(0);
        }
        SceneManager.LoadScene(0);
    }
    public void SkipBtn()
    {
        Time.timeScale = 1f;
        isSkiped = true;
        //upd.SetActive(false);
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

        fs.Close();
    }

}



