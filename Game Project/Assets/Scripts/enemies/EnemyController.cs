using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour
{

    public int health = 10;
    private Rigidbody rb;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody> ();
    }

    // Update is called once per frame
    void Update()
    {
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.layer == 3)
        {
            BulletController bulletScript;
            bulletScript = collision.gameObject.GetComponent<BulletController>();
            health -= bulletScript.damage;

            Vector3 dir = (transform.position - collision.transform.position).normalized;
            rb.AddForce(dir * bulletScript.knockback);
            Debug.Log(dir);

            Destroy(collision.gameObject);
        }
    }
}
