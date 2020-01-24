using UnityEngine;
using System.Collections;

public class COFlocking : MonoBehaviour {
	float speed = 0.001f;
	float rotationSpeed = 5.0f;
	Vector3 averageHeading;
	Vector3 averagePosition;
	
	public float neighbourDistance = 1.0f;
	public Vector3 avoidDist = new Vector3(5,5,5);
	public Vector3 externalForce = new Vector3(0,0,0);
	public Vector3 goalPosition = new Vector3(0,0,0);
	
	public float timeApplyRules = 0;
	
	public int bucket = 1; // 1 top left //2 top right //3 bottom left // bottom right
	
	public bool run= false;
	public bool freeMove= false;
	// Use this for initialization
	void Start () {
		speed = Random.Range(5f,7f);
	}
	
	void applyBucket() {
		if (transform.position.x < 12) {
			bucket = 1;
		}
		else {
			bucket = 2;
		}
	}
	
	public void setExternalForce(float x, float z) {
		externalForce.x = (float)x;
		externalForce.z = (float)z;
	}
	
	public void setNDist(float nDist) {
		neighbourDistance = nDist;
	}
	
	void ApplyRules () {
		GameObject[] gos;
		gos = GameObject.FindGameObjectsWithTag("flock");
		
		Vector3 vcentre = new Vector3(0,0,0);
		//Vector3 vavoid = new Vector3(5,5,5);
		float gSpeed = 0;;
		
		float dist;
		int groupSize = 0;
		
		//print("in "+goalPosition);
		
		foreach (GameObject go in gos) {
			if (go != this.gameObject) {
				if (bucket != go.GetComponent<COFlocking>().bucket) {
				//	return;
				}
				dist = Vector3.Distance(go.transform.position, this.transform.position);
				//print("dist ="+dist);
				if (dist <= neighbourDistance) {
					vcentre += go.transform.position;
					groupSize++;
					
					if (dist < 0.5) {
						avoidDist = avoidDist + (this.transform.position - go.transform.position);
					}
					
					if (go.GetComponent<COFlocking>() != null) {
						gSpeed += go.GetComponent<COFlocking>().speed;
					}
				}
			}
		}
		
		if (groupSize >0) {
			if (goalPosition != Vector3.zero) {
				vcentre = vcentre/groupSize + externalForce + (goalPosition - this.transform.position);
			}
			else {
				vcentre = vcentre/groupSize + externalForce;
			}
			
			speed = gSpeed/groupSize;
			
			Vector3 direction = (vcentre+avoidDist) - transform.position;
			//print("direction "+direction);
			if (direction != Vector3.zero) {
				transform.rotation = Quaternion.Slerp(transform.rotation,Quaternion.LookRotation(direction),rotationSpeed*Time.deltaTime);
			}
		}
		
	}
	
	// Update is called once per frame
	void Update () {
		//print("ss = "+Time.time);
		timeApplyRules = Time.realtimeSinceStartup;
		applyBucket();
		if (Random.Range(0,50) < 10) {
			//check bucket
			if (!freeMove) 
				ApplyRules();
		}
		if (freeMove) {
			if (transform.position.x < -40.0f) {
				transform.position = new Vector3(38,transform.position.y,transform.position.z);
			}
			else if (transform.position.x > 40.0f) {
				transform.position = new Vector3(-38,transform.position.y,transform.position.z);
			}
			
			if (transform.position.z < -15.0f) {
				transform.position = new Vector3(transform.position.x,transform.position.y,13);
			}
			else if (transform.position.z > 15.0f) {
				transform.position = new Vector3(transform.position.x,transform.position.y,-13);
			}
			
			if (transform.position.y > 24.0f) {
				transform.position = new Vector3(transform.position.x,-14,transform.position.z);
			}
			else if (transform.position.z < -15.0f) {
				transform.position = new Vector3(transform.position.x,23,transform.position.z);
			}
		}
		if (run) {
			transform.Translate(0,0,Time.deltaTime*speed);
		}
		timeApplyRules = Time.realtimeSinceStartup - timeApplyRules;
		
		
	}
}


