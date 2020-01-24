using UnityEngine.Networking;
using UnityEngine;

public class PlayerShoot : NetworkBehaviour
{
    private const string PLAYER_TAG = "Player";

    [SerializeField]
    private PlayerWeapon weapon;
    public WeaponGraphics currentGraphics;

    //[SerializeField]
    //private GameObject weaponGFX;

    [SerializeField]
    private Camera cam;

    [SerializeField]
    private LayerMask mask;

    // Use this for initialization
    void Start ()
    {
		if (cam == null)
        {
            Debug.LogError("No camera referenced!");
            this.enabled = false;
        }

        EquipGraphics(currentGraphics);
	}
	
	// Update is called once per frame
	void Update ()
    {
		if (Input.GetKey(KeyCode.Mouse0))
        {
            Shoot();
            currentGraphics.muzzleFlash.Play();
            currentGraphics.muzzleFlash1.Play();
            currentGraphics.muzzleFlash.Stop();
            currentGraphics.muzzleFlash1.Stop();
        }
	}

    public WeaponGraphics GetGraphics ()
    {
        return currentGraphics;
    }

    void EquipGraphics (WeaponGraphics graph)
    {
        currentGraphics = GetComponent<WeaponGraphics>();
    }

    [Client]
    void Shoot ()
    {
        RaycastHit hit;
        if (Physics.Raycast(cam.transform.position, cam.transform.forward, out hit, weapon.range, mask))
        {
            if (hit.collider.tag == PLAYER_TAG)
            {
                CmdPlayerShot(hit.collider.name, weapon.damage);
            }
        }
    }

    [Command]
    void CmdPlayerShot (string playerID, int damage)
    {
        Debug.Log(playerID + " has been shot.");

        PlayerManager player = GameManager.GetPlayer(playerID);
        player.RpcTakeDamage(damage);
    }
}
