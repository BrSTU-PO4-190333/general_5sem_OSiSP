using UnityEngine;

public class Bunker : MonoBehaviour
{
    private SpriteRenderer sp;
    private int health = 3;
    private void Awake()
    {
        sp = GetComponent<SpriteRenderer>();
    }
    private void OnTriggerEnter2D(Collider2D other)
    {
        if(other.gameObject.layer == LayerMask.NameToLayer("Missile")) {
            Color color = sp.material.color;
            color.a -= 0.3f;
            sp.material.color = color;
            health--;
        }
        if(health <= 0) {
            this.gameObject.SetActive(false);
        }
        if(other.gameObject.layer == LayerMask.NameToLayer("Invader")) {
            this.gameObject.SetActive(false);
        }
    }
}
