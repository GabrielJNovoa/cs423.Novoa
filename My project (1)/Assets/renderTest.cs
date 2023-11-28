using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class renderTest : MonoBehaviour
{
    RenderTexture rt;

    // Start is called before the first frame update
    void Start()
    {
        rt = new RenderTexture(256, 256, 0, RenderTextureFormat.Default);
    }

    // Update is called once per frame
    void Update()
    {
        RenderTexture.active = rt;
    }
}
