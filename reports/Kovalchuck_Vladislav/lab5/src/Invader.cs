using UnityEngine;
using Helper;
public class Invader : MonoBehaviour
{
    public Sprite[] animationSprites;
    public float animationTime = 1.0f;

    public System.Action killed;
    private SpriteRenderer _spriteRenderer;
    private int _animationFrame;
    public int health;
    private int totalHealth;



    private void Awake()
    {
        _spriteRenderer = GetComponent<SpriteRenderer>();
        totalHealth = this.health;
    }
    private void Start()
    {
        InvokeRepeating(nameof(AnimateSprite), this.animationTime, this.animationTime);
    }
    private void AnimateSprite()
    {
        _animationFrame++;
        if(_animationFrame >= this.animationSprites.Length)
        {
            _animationFrame = 0;
        }
        _spriteRenderer.sprite = this.animationSprites[_animationFrame];
    }
    private void OnTriggerEnter2D(Collider2D other)
    {
        if(other.gameObject.layer == LayerMask.NameToLayer("Laser"))
        {
            Helper.Helperdll.EnemyRecieveDamage(ref this.health);
        }
        if(health<=0)
        {
            Player.Score += 100 * totalHealth;
            this.killed.Invoke();
            this.gameObject.SetActive(false);
        }
    }
}
