using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Snake : MonoBehaviour
{
    private Vector2 _diraction = Vector2.right;

    private List<Transform> _segments = new List<Transform>();

    public Transform segmentPrefab;

    public int initialSize = 4;

    public int Score = 0;

    public GameObject ScoreText;

    public void Count()
    {
        Score++;
        ScoreText.GetComponent<Text>().text = "Score: " + Score.ToString();
        if(Score > 10)
        {
            Time.timeScale = Score/10;
        }
    }

    private void Start()
    {
        ResetState();
    }

    private void Update()
    {
            if(Input.GetKeyDown(KeyCode.W) && _diraction != Vector2.down) {
                _diraction = Vector2.up;
            }else if(Input.GetKeyDown(KeyCode.S) && _diraction != Vector2.up) {
                _diraction = Vector2.down;
            }else if(Input.GetKeyDown(KeyCode.A) && _diraction != Vector2.right) {
                _diraction = Vector2.left;
            }else if(Input.GetKeyDown(KeyCode.D) && _diraction != Vector2.left) {
                _diraction = Vector2.right;
            }else if(Input.GetKeyDown(KeyCode.R)) {
                SceneManager.LoadScene(1);
        }
    }

    private void  FixedUpdate()
    {
        for (int i = _segments.Count - 1; i > 0; i--)
        {
            _segments[i].position = _segments[i - 1].position;  
        }

        this.transform.position = new Vector3(
            Mathf.Round(this.transform.position.x) + _diraction.x,
            Mathf.Round(this.transform.position.y) + _diraction.y,
            0.0f
        );
    }

    private void Grow()
    {
        Transform segment = Instantiate(this.segmentPrefab);
        segment.position = _segments[_segments.Count - 1].position;

        _segments.Add(segment);
        Count();
    }

    private void ResetState()
    {
        for (int i = 1; i < _segments.Count; i++)
        {
            Destroy(_segments[i].gameObject);
        }    

            _segments.Clear();
            _segments.Add(this.transform);

            for (int i = 1; i < this.initialSize; i++)
            {
                _segments.Add(Instantiate(this.segmentPrefab));
            }

            this.transform.position = Vector3.zero;
        
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if(other.tag == "Food") {
        Grow();   
        } else if (other.tag == "Obstacle") {
            Time.timeScale = 0f;
        }
    }
}
