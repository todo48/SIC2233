#pragma once
#include<vector>
#include"Projectile.h"


class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();

	//XVˆ—
	void Update(float elapsedTime);

	//•`‰æˆ—
	void Render(ID3D11DeviceContext* dc, Shader* shader);
	
	//ƒfƒoƒbƒOƒvƒŠƒ~ƒeƒBƒu•`‰æ
	void DrawDebugPrimitive();

	// ’eŠÛ“o˜^
	void Register(Projectile* projectile);
	
	//’eŠÛ‘Síœ
	void Clear();

	//’eŠÛ”æ“¾
	int GetProjectileCount() const { return static_cast<int>(projectiles.size()); }

	//’eŠÛæ“¾
	Projectile* GetProjectile(int index) { return projectiles.at(index); }

	//’eŠÛíœ
	void Remove(Projectile* projectile);

private:
	std::vector<Projectile*> projectiles;
	std::vector<Projectile*> removes;
};