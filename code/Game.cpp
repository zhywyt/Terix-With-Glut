#include "Game.h"
#include <algorithm>
const int Game::dx = 1;
const int Game::dy = 1;
const int Game::rePx = Game::dx + GameRow / 2, Game::rePy = 0;
const int Game::waitPx = Game::dx * 3 + GameRow, Game::waitPy = Game::dy;
const int Game::infoPx = dx * 2 + GameRow, Game::infoPy = 5 * dx + 4;
Game::Game() 
	:status(PRESTART),_points(0),PB_points(0),PB_Diff(0), _ifs("BestPoints.zhywyt",
		fstream::in) , clearTimes(0),Diff(0),PB(false),zhywyt(18816),exZhywyt(false)
{
	m_map.resize(Row, vector<int>(Cow));
	srand((unsigned int)time(NULL));
	if (_ifs) {
		_ifs >> PB_points >> PB_Diff;
	}
	_ifs.close();
	for (int i = 0; i < Cow; i++) {
		//�����ǽ
		for (int j = 0; j < dx; j++)
			m_map[j][i] = WALL;
		//�м���ǽ
		for (int j = 1; j <= dx; j++)
			m_map[GameRow + j][i] = WALL;
		//�ұ���ǽ
		for (int j = 1; j <= dx; j++)
			m_map[Row - j][i] = WALL;

	}
	//���ϵ��º�ǽ
	for (int i = 0; i < dx; i++)
		for (int j = 0; j < Row - GameRow - 3 * dx; j++) {
			m_map[GameRow + 2 * dx + j][i] = WALL;
			m_map[GameRow + 2 * dx + j][Cow - 1 - i] = WALL;
		}
	//�м��ǽ
	for (int i = 0; i < Row - GameRow - 3 * dx; i++)m_map[GameRow + 2 * dx + i][4 + dx] = WALL;
	//next Toll�ұߵĺ��
	for (int i = 0; i < 4; i++)m_map[2 * dx + GameRow][dx + i] = WALL;
}

void Game::Start() {
	status = RUN;
	NextTool();
	NextTool();
}
void Game::Drop() {
	if (CanMoveDown()) {
		m_tool.run = true;
		m_tool.MoveDown();
	}
	else {
		AddToMap();
		NextTool();
	}
}
void Game::NextTool() {
	swap(m_tool, m_next);
	m_tool.setPosition(rePx, rePy);
	ToolType aType = ToolType(abs(rand()%(TTEnd-LL))+LL);
	m_next = Tool(waitPx, waitPy, aType);
}
void Game::reset() {
	PB = false;
	exZhywyt = false;
	status = PRESTART;
	_points = 0;
	clearTimes = 0;
	Diff = 0;
	for (int i = dx; i < GameRow+dx; i++)
		for (int j = 0; j < GameCow; j++)
			 m_map[i][j] = 0;
}
bool Game::CanMoveDown() {
	for(int i=0;i<4;i++)
		for (int j = 0; j < 4; j++) {
			if (m_tool._data[i][j]) {
				if (m_tool._y +j+ 1 < Cow) {
					if (m_map[m_tool._x+i][m_tool._y +j + 1])return false;
				}
				else return false;
			}
		}
	return true;
}
bool Game::CangetMoveRight() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (m_tool._data[i][j]) {
				if (m_tool._x +i+ 1 < dx+GameRow) {
					if (m_map[m_tool._x+i+1][m_tool._y+j ])return false;
				}
				else return false;
			}
		}
	return true;
}
bool Game::CangetMoveLeft() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (m_tool._data[i][j]) {
				if (m_tool._x+i - 1 > 0) {
					if (m_map[m_tool._x+i-1][m_tool._y+j ])return false;
				}
				else return false;
			}
		}
	return true;
}
//�����Ƚϴ�ֱ�ӽ����ˣ��жϱ任���ֿ�
bool Game::Rotate() {
	if (m_tool._type == DOT||m_tool._type==OO)return true;
	Tool revTool = m_tool.Rotate();
	for(int i=0;i<4;i++)
		for (int j = 0; j < 4; j++) 
			if (revTool._data[i][j]) 
				if (m_map[revTool._x+i][revTool._y+j])return false;
	//���û�г�ͻ��ֱ�ӽ���revTool��m_tool��������ƶ���ֵ�������е����ƣ�
	//��Ϊ�ҵ�m_tool�Ѿ�����Ҫ�ˣ�ֱ����revTool������������
	swap(m_tool, revTool);
	return true;
}
void Game::GameOver() {
	if (_points > PB_points) {
		PB = true;
		_ofs = ofstream("BestPoints.zhywyt", fstream::out);
		if (!_ofs) {
			cout << "Open file False in output" << endl;
			exit(-1);
		}
		_ofs << _points <<" " << PB_Diff << endl;
		PB_points = _points;
	}
	if (_points > zhywyt) {
		exZhywyt = true;
	}
	status = GAMEOVER;
}
void Game::AddToMap() {
	vector<int>test;
	//�Ȱ���Ϸ������뱳��
	for(int i=0;i<4;i++)
		for (int j = 0; j < 4; j++) 
			if (m_tool._data[i][j]) {
				m_map[i + m_tool._x][j + m_tool._y] = m_tool._data[i][j];
				test.push_back(j + m_tool._y);
			}
	//�����Ϸ�����Ƿ��������
	auto ibeg = test.begin();
	while (ibeg != test.end()) {
		int i = *ibeg;
		bool flag = true;
		for (int j = dx; j < GameRow; j++) {
			if (!m_map[j][i]) {
				flag = false;
				break;
			}
		}
		//���������� i ��
		if (flag) {
			//�� i ������������������ƶ�
			for (int k = i; k > 0; k--) {
				for (int j = dx; j < GameRow; j++) {
					m_map[j][k] = m_map[j][k - 1];
				}
			}
			//�Ѷ����ÿ�
			for (int j = dx; j < GameRow + dx; j++)
				m_map[j][0] = 0;
			clearTimes++;
			//����ӷ�
			_points += GameRow * clearTimes;
			if (_points > PB_points) {
				PB = true;
				PB_points = _points;
			}
		}
		//�����Ѷ�
		Diff = clearTimes / 3;
		ibeg++;
	}
	//��������ʱ�򷽿�û���ƶ����ж���Ϸ����
	if (!m_tool.run) {
		GameOver();
	}
}
int Game::getDiff()const {
	return Diff;
}
GameMode Game::getStatus() const {
	return status;
}
void Game::ChangeStatus(GameMode la) {
	status = la;
}

//��GameOver��ͬ��ǰ��ֻ������߷�Ŷ~
bool Game::Save(string FileName) {
	ofstream ofs(FileName, fstream::out);
	if (ofs) {
		//��������˳����
		ofs << status << " " << clearTimes << " "
			<< zhywyt << " " << _points << " "
			<< PB_points << " " << Diff << " "
			<< PB_Diff << " " << PB << endl;
		ofs << m_tool._type << " " << m_next._type << endl;
		for (int i = 0; i < Row; i++) {
			for (int j = 0; j < Cow; j++)
				ofs << m_map[i][j] << " ";
			ofs << endl;
		}
		return true;
	}
	return false;
}
bool Game::Load(string FileName) {
	ifstream ifs(FileName, fstream::in);
	if (ifs) {
		int Status, m_tool_Type, m_next_Type;
		ifs >> Status >> clearTimes
			>> zhywyt >> _points
			>> PB_points >> Diff
			>> PB_Diff >> PB
			>> m_tool_Type >> m_next_Type;
		for (int i = 0; i < Row; i++)
			for (int j = 0; j < Cow; j++)
				ifs >> m_map[i][j];
		status = GameMode(Status);
		m_tool = Tool(rePx,rePy,ToolType(m_tool_Type));
		m_next = Tool(waitPx, waitPy, ToolType(m_next_Type));
		return true;
	}
	return false;
}