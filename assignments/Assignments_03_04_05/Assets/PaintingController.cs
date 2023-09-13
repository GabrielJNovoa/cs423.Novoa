using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PaintingController : MonoBehaviour
{
    public Material[] materials;
    void Start()
    {
        randomizeTexture();
    }

    // Update is called once per frame
    void Update()
    {
    }

    void randomizeTexture()
    {
        GetComponent<Renderer>().material = materials[Random.Range(0, materials.Length)];
    }
}
