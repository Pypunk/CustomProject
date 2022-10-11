#pragma once
class Camera;
class GameObject;
class Texture;
class Level
{
public:
	Level();
	~Level();
	void Update(float elapsedSec);
	void Draw(Camera* camera) const;
	Rectf GetLevelShape() const;
	void ToggleDebugMode();

	void CreateLevelFromFile(const std::string& fileName);
	bool IsLevelEnded() const;
	void ActivatePortal() const;
private:
	std::vector<GameObject*> m_pObjects;
	Texture* m_pLevelTexture;
	std::vector<std::vector<Point2f>> m_Vertices;
	bool m_IsDebugMode;
	bool m_IsLevelEnded;

	void CreateObject(const std::string& object);
	void CreateBackgroundTexture(const std::string& texture);
	void CreatePlayer(const std::string& player);
	void CreateFoliage(const std::string& foliage);
	void CreateStone(const std::string& stone);
	void CreatePortal(const std::string& portal);
	Point2f ToPoint2f(const std::string& point2fStr) const;
	int ToFoliageTypeId(const std::string& typeStr) const;
	std::string GetAttributeValue(const std::string& attrName, const std::string& element) const;

	void UpdateGameObjects(float elapsedSec);
	void DrawDebugMode() const;
	void ClearLevel();
};

