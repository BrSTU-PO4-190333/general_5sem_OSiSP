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

    public Text version;
    public GameObject noviygod;
    public GameObject happychristmas;
    public GameObject snegopad;

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

    private void Awake()
    {
        Time.timeScale = 1f;
        if (UpdateController.isChristmas)
        {
            noviygod.SetActive(true);
            happychristmas.SetActive(true);
            snegopad.SetActive(true);
        }
    }
}







// using UnityEngine;
// using UnityEngine.SceneManagement;
// using UnityEngine.UI;
// using About;
// using Unity.RemoteConfig;

// public class MainMenu : MonoBehaviour
// {
//     public GameObject MessageBox;
//     public Text textAboutinf;
//     private AboutL information = new AboutL();

//     public Text textPlay;
//     public Text textExit;
//     public Text textAbout;

//     public Text version;
//     public GameObject UpdatePopUp;
//     public GameObject noviygod;
//     public GameObject happychristmas;
//     public GameObject snegopad;
//     public GameObject updateNowButton;
//     public struct userAttributes { }
//     public struct appAttributes { }
//     private bool isSkiped = false;

//     public void Play(int index)
//     {
//         SceneManager.LoadScene(index);
//     }
//     public void Exit()
//     {
//         Application.Quit();
//     }
//     public void About()
//     {
//         textAboutinf.text = information.InformationAbout();
//         MessageBox.SetActive(!MessageBox.activeSelf); 
//     }
//     public void Normal()
//     {
//         textPlay.fontStyle = FontStyle.Normal;
//         textExit.fontStyle = FontStyle.Normal;
//         textAbout.fontStyle = FontStyle.Normal;
//     }
//     public void Bold()
//     {
//         textPlay.fontStyle = FontStyle.Bold;
//         textExit.fontStyle = FontStyle.Bold;
//         textAbout.fontStyle = FontStyle.Bold;
//     }
//     public void Italic()
//     {
//         textPlay.fontStyle = FontStyle.Italic;
//         textExit.fontStyle = FontStyle.Italic;
//         textAbout.fontStyle = FontStyle.Italic;
//     }
//     public void UpdateButton()
//     {
//         SceneManager.LoadScene(0);
//     }
//     public void Skip()
//     {
//         isSkiped = true;
//         Time.timeScale = 1f;
//         UpdatePopUp.SetActive(false);
//     }

//     private void Awake()
//     {
//         Time.timeScale = 1f;
//         ConfigManager.FetchConfigs<userAttributes, appAttributes>
//                  (new userAttributes(), new appAttributes());
//         version.text = ConfigManager.appConfig.GetString("VersionString");
//         if (ConfigManager.appConfig.GetBool("isChristmas"))
//         {
//             noviygod.SetActive(true);
//             happychristmas.SetActive(true);
//             snegopad.SetActive(true);
//         }
//     }
//     private void Update()
//     {
//         ConfigManager.FetchConfigs<userAttributes, appAttributes>(new userAttributes(), new appAttributes());
        
//         if (version.text != ConfigManager.appConfig.GetString("VersionString") && isSkiped == false)
//         {
//             UpdatePopUp.SetActive(true);
//         }
//         if(Input.GetKeyDown(KeyCode.O))
//         {
//             SceneManager.LoadScene(2);
//         }
//         if(Input.GetKeyDown(KeyCode.I))
//         {
//             SceneManager.LoadScene(1);
//         }
//     }
// }

