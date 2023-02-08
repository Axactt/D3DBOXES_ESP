#include"hackLogic.h"
extern float gameWindowWidth ;
extern float gameWindowHeight ;
void HackLogic::Init()
{
	// This function will update and provide local Player and entity list pointer
	client = (ptrdiff_t) GetModuleHandleA( "Client.dll" );
	engine = (ptrdiff_t) GetModuleHandleA( "engine.dll" );
	entList = (EntList*) (client + dwEntityList);
	localEntity = entList->entlistObjPtrArray[0].entityObjPtr;

}

void HackLogic::Update()
{
	// this function continuously update ViewMatrix inside our Dll
	memcpy( &viewMatrix, (BYTE*) (client + dwViewMatrix), sizeof( viewMatrix ));
}

bool HackLogic::checkValidEnt( LocalEntity* ent )
{
	if (!ent)
		return false;
	if (ent == localEntity)
		return false;
	if (ent->iHealth <= 0)
		return false;
	if (ent->isDormant)
		return false;
	return true;
}

bool HackLogic::worldToScreen( Vec3 pos, Vec2& screen )
{
	Vec4 clipCoords;
	clipCoords.x = pos.x * viewMatrix[0] + pos.y * viewMatrix[1] + pos.z * viewMatrix[2] + viewMatrix[3];
	clipCoords.y = pos.x * viewMatrix[4] + pos.y * viewMatrix[5] + pos.z * viewMatrix[6] + viewMatrix[7];
	clipCoords.z = pos.x * viewMatrix[8] + pos.y * viewMatrix[9] + pos.z * viewMatrix[10] + viewMatrix[11];
	clipCoords.w = pos.x * viewMatrix[12] + pos.y * viewMatrix[13] + pos.z * viewMatrix[14] + viewMatrix[15];

	if (clipCoords.w < 0.1f)
		return false;
	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (gameWindowWidth / 2 * NDC.x) + (NDC.x + gameWindowWidth / 2);
	screen.y = -(gameWindowHeight / 2 * NDC.y) + (NDC.y + gameWindowHeight / 2);
	return true;
}

Vec3 HackLogic::GetBonePosition( LocalEntity* ent, int boneId )
 {
	/*
	//Matrix34 boneMatrix {};  // a matrix struct of 3x4 size Matrix[3][4]
	// Dereference added here to get the bone-base as an experiment
	//intptr_t bonePtr =  (intptr_t)*(intptr_t*)(*(intptr_t*)ent+0x26A8); // 

	DWORD oldProc {};
	VirtualProtect( &boneMatrix, 48, PAGE_EXECUTE_READWRITE, &oldProc );

	RtlMoveMemory( (char*) &boneMatrix, (char*) (bonePtr+ 0x30 * boneId), 48 );

	VirtualProtect( &boneMatrix, 48, oldProc, &oldProc );
	  
	Vec3 bonePosition { boneMatrix.m_matrix[0][3],boneMatrix.m_matrix[1][3],boneMatrix.m_matrix[2][3] };

	//bonePosition.x = *(float*) (bonePtr + 0x30 * boneId + 0x0C);
	//bonePosition.y = *(float*) (bonePtr + 0x30 * boneId + 0x1C);
	//bonePosition.z = *(float*) (bonePtr + 0x30 * boneId + 0x2C);  
	
	//bonePosition.x = boneMatrix.m_matrix[0][3];
	//bonePosition.y = boneMatrix.m_matrix[1][3];
	//bonePosition.z = boneMatrix.m_matrix[2][3];    */

	// ent pointer cast to integer address
	//offset 0x26a8 added up and the value read from the final integer address
	intptr_t bonePtr = *(intptr_t*) ((intptr_t) ent + 0x26A8); 
	Vec3 bonePosition ;
	bonePosition.x = *(float*) (bonePtr + 0x30 * boneId + 0x0C);
	bonePosition.y = *(float*) (bonePtr + 0x30 * boneId + 0x1C);
	bonePosition.z = *(float*) (bonePtr + 0x30 * boneId + 0x2C);  
	return bonePosition;
}