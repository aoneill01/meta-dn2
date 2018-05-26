<Query Kind="Program">
  <Namespace>System.Drawing</Namespace>
</Query>



void Main()
{
	Bitmap map = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\level2.png"), true);
	
	map.Dump();
	
	string result = "";
	
	for (int y = 0; y < map.Height; y++)
	{
		string tmp = "";
		for (int x = 0; x < map.Width; x ++) 
		{
			if (!string.IsNullOrEmpty(tmp)) 
			{
				tmp += ", ";
			}
			
			if (!IsSolid(map, x, y)) {
				tmp += "0, 0";
			}
			else {
				int tile = GetTile(map, x, y);
				
				tmp += (START_INDEX + tile * 4) + ", " + (START_INDEX + tile * 4 + 1);
			}
		}
		result += "{" + tmp + "},\n";
		tmp = "";
		
		for (int x = 0; x < map.Width; x ++) 
		{
			if (!string.IsNullOrEmpty(tmp)) 
			{
				tmp += ", ";
			}
			
			if (!IsSolid(map, x, y)) {
				tmp += "0, 0";
			}
			else {
				int tile = GetTile(map, x, y);
				
				tmp += (START_INDEX + tile * 4 + 2) + ", " + (START_INDEX + tile * 4 + 3);
			}
		
		}
		result += "{" + tmp + "},\n";
	}
	
	result = "const uint16_t layer1[LAYER_HEIGHT][LAYER_WIDTH] = {\n" + result + "};";
	result.Dump();
}

static int START_INDEX = 35;

static int INTERIOR_1 = 4;
static int INTERIOR_2 = 20;
static int INTERIOR_3 = 21;
static int NORTH_WEST_CORNER = 0;
static int NORTH_EDGE = 1;
static int NORTH_EAST_CORNER = 2;
static int WEST_EDGE = 3;
static int EAST_EDGE = 5;
static int SOUTH_WEST_CORNER = 6;
static int SOUTH_EDGE = 7;
static int SOUTH_EAST_CORNER = 8;
static int NORTH_VERTICAL = 9;
static int MIDDLE_VERTICAL = 10;
static int SOUTH_VERTICAL = 11;
static int WEST_HORIZONTAL = 12;
static int MIDDLE_HORIZONTAL = 13;
static int EAST_HORIZONTAL = 14;
static int ONE_BY_ONE = 15;
static int SOUTH_EAST_BEND = 16;
static int SOUTH_WEST_BEND = 17;
static int NORTH_EAST_BEND = 18;
static int NORTH_WEST_BEND = 19;

int GetTile(Bitmap map, int x, int y) 
{
	if (!IsNorthSolid(map, x, y) && IsEastSolid(map, x, y) && IsSouthSolid(map, x, y) && !IsWestSolid(map, x, y)) return NORTH_WEST_CORNER;
	if (!IsNorthSolid(map, x, y) && IsEastSolid(map, x, y) && IsSouthSolid(map, x, y) && IsWestSolid(map, x, y)) return NORTH_EDGE;
	if (!IsNorthSolid(map, x, y) && !IsEastSolid(map, x, y) && IsSouthSolid(map, x, y) && IsWestSolid(map, x, y)) return NORTH_EAST_CORNER;
	if (!IsNorthSolid(map, x, y) && IsEastSolid(map, x, y) && IsSouthSolid(map, x, y) && !IsWestSolid(map, x, y)) return NORTH_WEST_CORNER;
	if (IsNorthSolid(map, x, y) && IsEastSolid(map, x, y) && IsSouthSolid(map, x, y) && !IsWestSolid(map, x, y)) return WEST_EDGE;
	if (IsNorthSolid(map, x, y) && !IsEastSolid(map, x, y) && IsSouthSolid(map, x, y) && IsWestSolid(map, x, y)) return EAST_EDGE;
	if (IsNorthSolid(map, x, y) && IsEastSolid(map, x, y) && !IsSouthSolid(map, x, y) && !IsWestSolid(map, x, y)) return SOUTH_WEST_CORNER;
	if (IsNorthSolid(map, x, y) && IsEastSolid(map, x, y) && !IsSouthSolid(map, x, y) && IsWestSolid(map, x, y)) return SOUTH_EDGE;
	if (IsNorthSolid(map, x, y) && !IsEastSolid(map, x, y) && !IsSouthSolid(map, x, y) && IsWestSolid(map, x, y)) return SOUTH_EAST_CORNER;
	if (!IsNorthSolid(map, x, y) && !IsEastSolid(map, x, y) && IsSouthSolid(map, x, y) && !IsWestSolid(map, x, y)) return NORTH_VERTICAL;
	if (IsNorthSolid(map, x, y) && !IsEastSolid(map, x, y) && IsSouthSolid(map, x, y) && !IsWestSolid(map, x, y)) return MIDDLE_VERTICAL;
	if (IsNorthSolid(map, x, y) && !IsEastSolid(map, x, y) && !IsSouthSolid(map, x, y) && !IsWestSolid(map, x, y)) return SOUTH_VERTICAL;
	if (!IsNorthSolid(map, x, y) && IsEastSolid(map, x, y) && !IsSouthSolid(map, x, y) && !IsWestSolid(map, x, y)) return WEST_HORIZONTAL;
	if (!IsNorthSolid(map, x, y) && IsEastSolid(map, x, y) && !IsSouthSolid(map, x, y) && IsWestSolid(map, x, y)) return MIDDLE_HORIZONTAL;
	if (!IsNorthSolid(map, x, y) && !IsEastSolid(map, x, y) && !IsSouthSolid(map, x, y) && IsWestSolid(map, x, y)) return EAST_HORIZONTAL;
	if (!IsNorthSolid(map, x, y) && !IsEastSolid(map, x, y) && !IsSouthSolid(map, x, y) && !IsWestSolid(map, x, y)) return ONE_BY_ONE;
	if (IsNorthSolid(map, x, y) && IsEastSolid(map, x, y) && IsSouthSolid(map, x, y) && IsWestSolid(map, x, y)) 
	{
		if (!IsSouthEastSolid(map, x, y)) return SOUTH_EAST_BEND;
		if (!IsSouthWestSolid(map, x, y)) return SOUTH_WEST_BEND;
		if (!IsNorthEastSolid(map, x, y)) return NORTH_EAST_BEND;
		if (!IsNorthWestSolid(map, x, y)) return NORTH_WEST_BEND;
		
		if ((x * 3 + y * 5) % 19 == 0) return INTERIOR_2;
		if ((x * 5 + y * 3) % 17 == 0) return INTERIOR_3;
	}
	
	return INTERIOR_1;
}

bool IsNorthSolid(Bitmap map, int x, int y) 
{
	return IsSolid(map, x, y - 1);
}

bool IsSouthSolid(Bitmap map, int x, int y) 
{
	return IsSolid(map, x, y + 1);
}

bool IsWestSolid(Bitmap map, int x, int y)
{
	return IsSolid(map, x - 1, y);
}

bool IsEastSolid(Bitmap map, int x, int y)
{
	return IsSolid(map, x + 1, y);
}

bool IsSouthEastSolid(Bitmap map, int x, int y) 
{
	return IsSolid(map, x + 1, y + 1);
}

bool IsSouthWestSolid(Bitmap map, int x, int y) 
{
	return IsSolid(map, x - 1, y + 1);
}

bool IsNorthEastSolid(Bitmap map, int x, int y) 
{
	return IsSolid(map, x + 1, y - 1);
}

bool IsNorthWestSolid(Bitmap map, int x, int y) 
{
	return IsSolid(map, x - 1, y - 1);
}

bool IsSolid(Bitmap map, int x, int y) 
{
	if (x < 0) x += map.Width;
	if (x >= map.Width) x -= map.Width;
	if (y < 0 || y >= map.Height) return true;
	
	return map.GetPixel(x, y).R == 0;
}

int ColorToRgb565(Color color) 
{
	return ((color.R & 0xF8) << 8) | ((color.G & 0xFC) << 3) | (color.B >> 3);
}

int SwapEndian16(int value) 
{
	return ((value & 0xff00) >> 8) | ((value & 0xff) << 8);
}

string ToZeroPaddedHex4(int value) 
{
	return value.ToString("X").PadLeft(4, '0');
}