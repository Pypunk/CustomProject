#pragma once
#include <vector>
class Unit;
class UnitManager
{
public:
	enum class Type
	{
		villager,
		infantry,
		cavalry
	};
	UnitManager();
	~UnitManager();
	UnitManager(const UnitManager& other) = delete;
	UnitManager(UnitManager&& other) = delete;
	UnitManager& operator=(const UnitManager& other) = delete;
	UnitManager& operator=(UnitManager&& other) = delete;

	void Update(float elapsedSec);
	void Draw() const;
	void AddUnit(const Type& type, const Point2f& position);
	void SelectUnits(const Point2f& mousePos, const Rectf& selectionRect);
	void CheckAmountSelected();
	void MoveUnits(const Point2f& mousePos);
	void DoubleClickSelect(const Point2f& mousePos, bool doubleClickDetected, const Rectf& cameraRect);
private:
	int m_AmountSelected;
	std::vector<int> m_SelectedIndexes;
	std::vector<Unit*> m_pUnits;
	std::vector<Point2f> m_MovePositions;
	void SetColsAndRows(int amount, int& cols, int& rows, std::vector<int>& indexes, const Point2f& mousePos);
	void SetMovePositions(int amount, int& cols, int& rows, std::vector<Point2f>& movePositions, std::vector<int>& indexes, const Point2f& mousePos);
};

