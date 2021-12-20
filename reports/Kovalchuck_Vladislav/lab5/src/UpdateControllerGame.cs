using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class UpdateControllerGame : MonoBehaviour
{
    public Text version;
    public GameObject snegopad;
    public GameObject[] snow;
    public GameObject levelText;
    private void Awake()
    {
        version.text = UpdateController.VersionStr;
        if (UpdateController.isChristmas)
        {
            snegopad.SetActive(true);
            foreach (GameObject s in snow)
                s.SetActive(true);
        }
        if(UpdateController.isNewLvl)
        {
            levelText.SetActive(true);
        }
    }
    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.I))
        {
            SceneManager.LoadScene(1);
        }
        if(Input.GetKeyDown(KeyCode.O))
        {
            SceneManager.LoadScene(2);
        }
    }
}
