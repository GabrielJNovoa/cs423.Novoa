using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public float forwardSpeed;
    public float strafeSpeed;
    public float verticalSpeed;

    public float pitchSpeed;
    public float yawSpeed;
    public float rollSpeed;

    Rigidbody rigid;

    // Start is called before the first frame update
    void Start()
    {
        rigid = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        rigid.AddForce(transform.forward * Input.GetAxis("Vertical") * forwardSpeed);
        rigid.AddForce(transform.right * Input.GetAxis("Horizontal") * strafeSpeed);
        rigid.AddForce(transform.up * Input.GetAxis("Jump") * verticalSpeed);

        rigid.AddTorque(transform.up * Input.GetAxis("Mouse X") * pitchSpeed);
        rigid.AddTorque(transform.right * -Input.GetAxis("Mouse Y") * yawSpeed);
        rigid.AddTorque(transform.forward * Input.GetAxis("Roll") * rollSpeed);
    }
}
