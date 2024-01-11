#pragma once

	class Position {
	private:
		int X=0;
		int Y=0;
	public:
		Position(int x, int y);
		void incX(int j);
		void incY(int j);
		int getY() const;
		int getX() const;
};
