using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;

public class PlayerController : MonoBehaviour
{
    public float speed;
    public float boostSpeed;
    public int maxHealth = 100;
    private int health;

    public int maxStamina;
    public float staminaRegen;
    private int stamina;
    private float staminaTimer;

    public float pitchSpeed;
    public float yawSpeed;
    public float rollSpeed;

    public GameObject[] bullets;

    public GameObject steerObject;
    public GameObject velObject;
    public GameObject parallelObject;
    public GameObject perpendicularObject;

    Rigidbody rigid;

    // Start is called before the first frame update
    void Start()
    {
        rigid = GetComponent<Rigidbody>();
        stamina = maxStamina;
        health = maxHealth;
    }

    // Update is called once per frame
    void Update()
    {

        Vector3 steering = Vector3.zero;
        steering += transform.forward * Input.GetAxisRaw("Vertical");
        steering += transform.right * Input.GetAxisRaw("Horizontal");
        steering += transform.up * Input.GetAxisRaw("Jump");
        steering.Normalize();

        rigid.AddForce(steering*speed);

        rigid.AddTorque(transform.up * Input.GetAxisRaw("Mouse X") * pitchSpeed);
        rigid.AddTorque(transform.right * -Input.GetAxisRaw("Mouse Y") * yawSpeed);
        rigid.AddTorque(transform.forward * Input.GetAxisRaw("Roll") * rollSpeed);

        if (Input.GetButtonDown("Dash") && stamina > 0)
        {
            stamina -= 1;
            if (steering.magnitude != 0)
            {
                rigid.AddForce(steering.normalized * boostSpeed, ForceMode.Impulse);
            }
            else
            {
                rigid.AddForce(transform.forward * boostSpeed, ForceMode.Impulse);
            }
        }
        if (Input.GetButtonDown("Fire1"))
        {
            Instantiate(bullets[0], transform.position + transform.forward, transform.rotation);
        }

        if (stamina < maxStamina)
        {
            if (staminaTimer <= 0)
            {
                stamina += 1;
                staminaTimer = staminaRegen;
            }
            staminaTimer -= Time.deltaTime;
        }
    }
}
