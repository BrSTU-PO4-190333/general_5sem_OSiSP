using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using Unity.RemoteConfig;

public class Player : MonoBehaviour
{
    public Projectile lasetPrefab;
    public float speed = 5f;
    private bool _laserActive;
    public int Health;
    public static int Score = 0;

    public Text scoreText;

    private void Awake()
    {
        Score = 0;
        speed = 5f;
    }
    private void Update()
    {
        if(Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow)){
            this.transform.position += Vector3.left * this.speed * Time.deltaTime;
        } else if(Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow)){
            this.transform.position += Vector3.right * this.speed * Time.deltaTime;
        }
        if(Input.GetKeyDown(KeyCode.Space) || Input.GetMouseButtonDown(0))
        {
            Shoot();
        }
        if(Input.GetKeyDown(KeyCode.Escape))
        {
            SceneManager.LoadScene(0);
        }
        scoreText.text = $"Score: {Score}";
    }
    private void Shoot()
    {
        if(!_laserActive){
            Projectile projectile = Instantiate(this.lasetPrefab, this.transform.position, Quaternion.identity);
            projectile.destroyed += LaserDestroyed;
            _laserActive = true;
        }
    }
    private void LaserDestroyed()
    {
        _laserActive = false;
    }
    private void OnTriggerEnter2D(Collider2D other)
    {
        if(other.gameObject.layer == LayerMask.NameToLayer("Invader")||
        other.gameObject.layer == LayerMask.NameToLayer("Missile"))
        { 
            Helper.Helperdll.PLayerRecieveDamage(ref this.Health);
            if(this.Health <= 0)
            {
                SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            }  
        }
    }
}




// using UnityEngine;
// using UnityEngine.SceneManagement;
// using UnityEngine.UI;
// using Unity.RemoteConfig;

// public class Player : MonoBehaviour
// {
//     public Projectile lasetPrefab;
//     public float speed;
//     private bool _laserActive;
//     public int Health;
//     public static int Score = 0;

//     public Text scoreText;

//     public struct userAttributes { }
//     public struct appAttributes { }

//     private void Awake()
//     {
//         ConfigManager.FetchConfigs<userAttributes, appAttributes>(new userAttributes(), new appAttributes());
//         Score = 0;
//         speed = ConfigManager.appConfig.GetFloat("PlayerSpeed");
//         if(speed == 0f)
//         {
//             speed = 5f;
//         }
//     }
//     private void Update()
//     {
//         if(Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow)){
//             this.transform.position += Vector3.left * this.speed * Time.deltaTime;
//         } else if(Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow)){
//             this.transform.position += Vector3.right * this.speed * Time.deltaTime;
//         }
//         if(Input.GetKeyDown(KeyCode.Space) || Input.GetMouseButtonDown(0))
//         {
//             Shoot();
//         }
//         if(Input.GetKeyDown(KeyCode.Escape))
//         {
//             SceneManager.LoadScene(0);
//         }
//         scoreText.text = $"Score: {Score}";
//     }
//     private void Shoot()
//     {
//         if(!_laserActive){
//             Projectile projectile = Instantiate(this.lasetPrefab, this.transform.position, Quaternion.identity);
//             projectile.destroyed += LaserDestroyed;
//             _laserActive = true;
//         }
//     }
//     private void LaserDestroyed()
//     {
//         _laserActive = false;
//     }
//     private void OnTriggerEnter2D(Collider2D other)
//     {
//         if(other.gameObject.layer == LayerMask.NameToLayer("Invader")||
//         other.gameObject.layer == LayerMask.NameToLayer("Missile"))
//         { 
//             Helper.Helperdll.PLayerRecieveDamage(ref this.Health);
//             if(this.Health <= 0)
//             {
//                 SceneManager.LoadScene(SceneManager.GetActiveScene().name);
//             }  
//         }
//     }
// }
