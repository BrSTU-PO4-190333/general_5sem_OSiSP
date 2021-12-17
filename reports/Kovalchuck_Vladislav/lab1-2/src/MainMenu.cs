using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using About;

public class MainMenu : MonoBehaviour
{
    public GameObject MessageBox;
    public Text textAboutinf;
    private AboutL information = new AboutL();

    public Text textPlay;
    public Text textExit;
    public Text textAbout;
        
    public void Play(int index)
    {
        SceneManager.LoadScene(index);
    }
    public void Exit()
    {
        Application.Quit();
    }
    public void About()
    {
        textAboutinf.text = information.InformationAbout();
        MessageBox.SetActive(!MessageBox.activeSelf); 
    }
    public void Normal()
    {
        textPlay.fontStyle = FontStyle.Normal;
        textExit.fontStyle = FontStyle.Normal;
        textAbout.fontStyle = FontStyle.Normal;
    }
    public void Bold()
    {
        textPlay.fontStyle = FontStyle.Bold;
        textExit.fontStyle = FontStyle.Bold;
        textAbout.fontStyle = FontStyle.Bold;
    }
    public void Italic()
    {
        textPlay.fontStyle = FontStyle.Italic;
        textExit.fontStyle = FontStyle.Italic;
        textAbout.fontStyle = FontStyle.Italic;
    }
}
