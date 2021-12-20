using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine;
using Snakedll;

public class MainMenu : MonoBehaviour
{

    public Text text;
    public About sdll = new About();
    public GameObject textbox;
    public Text starttext;
    public Text abouttext;
    public Text exittext;
    public void start(int index)
    {
        SceneManager.LoadScene(index);
    }

    public void About()
    {
        text.text = sdll.Information();
        textbox.SetActive(!textbox.activeSelf);

    }

    public void Exit()
    {
        Application.Quit();
    }

    public void Bold()
    {
        starttext.fontStyle = FontStyle.Bold;
        abouttext.fontStyle = FontStyle.Bold;
        exittext.fontStyle = FontStyle.Bold;
    }

    public void Default()
    {
        starttext.fontStyle = FontStyle.Normal;
        abouttext.fontStyle = FontStyle.Normal;
        exittext.fontStyle = FontStyle.Normal;
    }
}
