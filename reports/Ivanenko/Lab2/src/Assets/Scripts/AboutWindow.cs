using UnityEditor;
using UnityEngine;
using AboutWindowApi;

public class AboutWindow : EditorWindow
{
    [MenuItem("Window/About")]
    public static void ShowWindow()
    {
        GetWindow<AboutWindow>("About window");
    }
        
    private void OnGUI()
    {
        GUILayout.Label(AboutWindowData.AboutInfoText, EditorStyles.boldLabel);
        AboutWindowData.AboutInfoText = EditorGUILayout.TextField("Enter some info: ", AboutWindowData.AboutInfoText);
        Repaint();
    }
}
