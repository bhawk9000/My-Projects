using UnityEngine;
using System.Collections;

public class COFlockingManager : MonoBehaviour {
	float m_stickCount;
	public Transform virusPrefab;
	public Transform fireworkPar;
	public Transform handfollow;
	
	public bool isCohesion = false;
	public bool isFreeMove = false;
	
	public bool isTimer = false;
	public bool isFollowMouse = true;
	int fish = 0;
	float loopCount = 0;
	float timeAVG = 0;
		
	public Vector3 goldPos = new  Vector3(0,0,0);
	void Start () {
		m_stickCount = 0;
	}
	
	public void setGoalPosition (Vector3 goalPos) {
		for (int i=0; i<transform.GetChildCount(); i++) {
			transform.GetChild(i).GetComponent<COFlocking>().run = true;
			transform.GetChild(i).GetComponent<COFlocking>().goalPosition = goalPos;
		}
	}
	
	public void setFreeMove () {
		for (int i=0; i<transform.GetChildCount(); i++) {
			transform.GetChild(i).GetComponent<COFlocking>().freeMove = true;
		}
	}
	
	public void CreateVirus(Vector3 pos) {
		Quaternion rotate = new Quaternion(0,0,0,0);
		Transform vNew = Instantiate(virusPrefab,pos,rotate) as Transform;
		vNew.parent = transform;
		Transform vNew2 = Instantiate(virusPrefab,pos,rotate) as Transform;
		vNew2.parent = transform;
		
		Instantiate(fireworkPar,pos,rotate);
	}
	
	public void setExternalForce(float x,float z) {
		for (int i=0; i<transform.GetChildCount(); i++) {
			transform.GetChild(i).GetComponent<COFlocking>().setExternalForce(x,z);
		}
	}
	
	public void EnableCohesion() {
		isCohesion = true;
		isFreeMove = false;
		for (int i=0; i<transform.GetChildCount(); i++) {
			transform.GetChild(i).GetComponent<COFlocking>().freeMove = false;
		}
		
	
	}
	public void EnableFreeMove() {
		isCohesion = false;
		isFreeMove = true;
		setFreeMove();
	
	}
	
	public void setNDist(float nDist) {
		for (int i=0; i<transform.GetChildCount(); i++) {
			transform.GetChild(i).GetComponent<COFlocking>().setNDist(nDist);
		}
	}
	
	void timerFunction() {
		float loopTime = 0;
		for (int i=0; i<transform.childCount;i++) {
			loopTime += transform.GetChild(i).GetComponent<COFlocking>().timeApplyRules;
		}
		if (fish != transform.childCount) {
			loopCount = 0;
			timeAVG = 0;
		}
		loopCount++;
		timeAVG += loopTime*1000;
		print("Fish = "+transform.childCount+"   and Time = "+(timeAVG/loopCount));
	}
	
	// Update is called once per frame
	void Update () {
		if (isCohesion) {
			if (isFollowMouse) {
				Vector3 mousePos = Input.mousePosition;
				mousePos.z = -10.0f;
				Vector3 worldPos = Camera.main.ScreenToWorldPoint(mousePos);
				worldPos.z = -10.0f;
				worldPos.x = -worldPos.x;
				worldPos.y = -worldPos.y;
			//handfollow.transform.position = worldPos;
				setGoalPosition(worldPos);
			}
			else {
				//setGoalPosition(new Vector3(0,0,0));
				Vector3 mousePos = Input.mousePosition;
				//mousePos.y = 0.0f;
				Vector3 worldPos = Camera.main.ScreenToWorldPoint(mousePos);
				//worldPos.z = worldPos.y;
				worldPos.x = -worldPos.x;
				worldPos.y = 0;
			//handfollow.transform.position = worldPos;
				setGoalPosition(worldPos);
			}
			//print(worldPos);
			//setGoalPosition(handfollow.transform.position);
		}
		else {
			setFreeMove();
		}
		//setGoalPosition(goldPos);
	}
	
	void LateUpdate() {
		if (isTimer) {
			timerFunction();
		}
	}
}
