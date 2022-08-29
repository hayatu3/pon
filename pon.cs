using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cube_move : MonoBehaviour
{
    private Vector3 v3Position = new Vector3(0.0f, 0.5f, 0.0f);

    private Vector3 v3Velocity = new Vector3(0.1f, 0.0f, 0.0f);
    private Vector3 v3Velocity2 = new Vector3(0.0f, 0.0f, 0.2f);

    // Start is called before the first frame update
    void Start()
    {
        transform.position = v3Position;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        v3Position += v3Velocity;//x
        v3Position += v3Velocity2;//y
        if (v3Position.x > 5.0f)//右
        {
            v3Position.x = 5.0f;
            v3Velocity.x = -v3Velocity.x;
        }
        if (v3Position.x < -5.0f)//左
        {
            v3Position.x = -5.0f;
            v3Velocity.x = -v3Velocity.x;
        }

        if (v3Position.z > 5.0f)//上
        {
            v3Position.z = 5.0f;
            v3Velocity2.z = -v3Velocity2.z;//y
        }
        if (v3Position.z < -5.0f)//下
        {
            v3Position.z = -5.0f;
            v3Velocity2.z = -v3Velocity2.z;//y
        }
        Debug.Log("x"+v3Position.x +"y"+ v3Position.z);
        transform.position = v3Position;
    }
}


