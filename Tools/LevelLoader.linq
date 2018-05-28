<Query Kind="Program">
  <Namespace>System.Drawing</Namespace>
</Query>

void Main()
{
	Bitmap map = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\level2.png"), true);
	Bitmap bg = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\background.png"), true);
	
	map.Dump();
	bg.Dump();
	
	GetCode(map, true, false).Dump();
	GetCode(map, true, true).Dump();
	
	GetCode(bg, false, false).Dump();
}

public string GetCode(Bitmap map, bool isMainMap, bool isHitMap) 
{
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
			
			tmp += GetTile(map, x, y, isMainMap, isHitMap);
		}
		result += "{" + tmp + "},\n";	
	}
	
	result = "const uint8_t layer1[LAYER_HEIGHT][LAYER_WIDTH] = {\n" + result + "};";
	
	return result;
}

class TileMap
{
	public int Interior1 { get; set; }
	public int Interior2 { get; set; }
	public int Interior3 { get; set; }
	public int NorthWestCorner { get; set; }
	public int NorthEdge { get; set; }
	public int NorthEastCorner { get; set; }
	public int WestEdge { get; set; }
	public int EastEdge { get; set; }
	public int SouthWestCorner { get; set; }
	public int SouthEdge { get; set; }
	public int SouthEastCorner { get; set; }
	public int NorthVertical{ get; set; }
	public int MiddleVertical { get; set; }
	public int SouthVertical { get; set; }
	public int WestHorizontal { get; set; }
	public int MiddleHorizontal { get; set; }
	public int EastHorizontal { get; set; }
	public int OneByOne { get; set; }
	public int SouthEastBend { get; set; }
	public int SouthWestBend { get; set; }
	public int NorthEastBend { get; set; }
	public int NorthWestBend { get; set; }
	public int Empty { get; set; }
}

static int EMPTY = 21;

static TileMap ForegroundMap = new TileMap
{
	Interior1 = 17,
	Interior2 = 66,
	Interior3 = 82,
	NorthWestCorner = 0,
	NorthEdge = 1,
	NorthEastCorner = 2,
	WestEdge = 16,
	EastEdge = 18,
	SouthWestCorner = 32,
	SouthEdge = 33,
	SouthEastCorner = 34,
	NorthVertical = 3,
	MiddleVertical = 19,
	SouthVertical = 35,
	WestHorizontal = 48,
	MiddleHorizontal = 49,
	EastHorizontal = 50,
	OneByOne = 51,
	SouthEastBend = 64,
	SouthWestBend = 65,
	NorthEastBend = 80,
	NorthWestBend = 81, 
	Empty = EMPTY
};

static TileMap AltForegroundMap = new TileMap
{
	Interior1 = ForegroundMap.Interior1,
	Interior2 = ForegroundMap.Interior2,
	Interior3 = ForegroundMap.Interior3,
	NorthWestCorner = ForegroundMap.NorthWestCorner + 4,
	NorthEdge = ForegroundMap.NorthEdge + 4,
	NorthEastCorner = ForegroundMap.NorthEastCorner + 4,
	WestEdge = ForegroundMap.WestEdge + 4,
	EastEdge = ForegroundMap.EastEdge + 4,
	SouthWestCorner = ForegroundMap.SouthWestCorner + 4,
	SouthEdge = ForegroundMap.SouthEdge + 4,
	SouthEastCorner = ForegroundMap.SouthEastCorner + 4,
	NorthVertical = ForegroundMap.NorthVertical + 4,
	MiddleVertical = ForegroundMap.MiddleVertical + 4,
	SouthVertical = ForegroundMap.SouthVertical + 4,
	WestHorizontal = ForegroundMap.WestHorizontal + 4,
	MiddleHorizontal = ForegroundMap.MiddleHorizontal + 4,
	EastHorizontal = ForegroundMap.EastHorizontal + 4,
	OneByOne = ForegroundMap.OneByOne + 4,
	SouthEastBend = ForegroundMap.SouthEastBend,
	SouthWestBend = ForegroundMap.SouthWestBend,
	NorthEastBend = ForegroundMap.NorthEastBend,
	NorthWestBend = ForegroundMap.NorthWestBend, 
	Empty = EMPTY
};

static TileMap MiddlegroundMap = new TileMap
{
	Interior1 = ForegroundMap.Interior1 + 8,
	Interior2 = ForegroundMap.Interior2 + 8,
	Interior3 = ForegroundMap.Interior3 + 8,
	NorthWestCorner = ForegroundMap.NorthWestCorner + 8,
	NorthEdge = ForegroundMap.NorthEdge + 8,
	NorthEastCorner = ForegroundMap.NorthEastCorner + 8,
	WestEdge = ForegroundMap.WestEdge + 8,
	EastEdge = ForegroundMap.EastEdge + 8,
	SouthWestCorner = ForegroundMap.SouthWestCorner + 8,
	SouthEdge = ForegroundMap.SouthEdge + 8,
	SouthEastCorner = ForegroundMap.SouthEastCorner + 8,
	NorthVertical = ForegroundMap.NorthVertical + 8,
	MiddleVertical = ForegroundMap.MiddleVertical + 8,
	SouthVertical = ForegroundMap.SouthVertical + 8,
	WestHorizontal = ForegroundMap.WestHorizontal + 8,
	MiddleHorizontal = ForegroundMap.MiddleHorizontal + 8,
	EastHorizontal = ForegroundMap.EastHorizontal + 8,
	OneByOne = ForegroundMap.OneByOne + 8,
	SouthEastBend = ForegroundMap.SouthEastBend + 8,
	SouthWestBend = ForegroundMap.SouthWestBend + 8,
	NorthEastBend = ForegroundMap.NorthEastBend + 8,
	NorthWestBend = ForegroundMap.NorthWestBend + 8, 
	Empty = EMPTY
};

static TileMap BackgroundMap = new TileMap
{
	Interior1 = ForegroundMap.Interior1 + 12,
	Interior2 = ForegroundMap.Interior1 + 12,
	Interior3 = ForegroundMap.Interior3 + 12,
	NorthWestCorner = ForegroundMap.NorthWestCorner + 12,
	NorthEdge = ForegroundMap.NorthEdge + 12,
	NorthEastCorner = ForegroundMap.NorthEastCorner + 12,
	WestEdge = ForegroundMap.WestEdge + 12,
	EastEdge = ForegroundMap.EastEdge + 12,
	SouthWestCorner = ForegroundMap.SouthWestCorner + 12,
	SouthEdge = ForegroundMap.SouthEdge + 12,
	SouthEastCorner = ForegroundMap.SouthEastCorner + 12,
	NorthVertical = ForegroundMap.NorthVertical + 12,
	MiddleVertical = ForegroundMap.MiddleVertical + 12,
	SouthVertical = ForegroundMap.SouthVertical + 12,
	WestHorizontal = ForegroundMap.WestHorizontal + 12,
	MiddleHorizontal = ForegroundMap.MiddleHorizontal + 12,
	EastHorizontal = ForegroundMap.EastHorizontal + 12,
	OneByOne = ForegroundMap.OneByOne + 12,
	SouthEastBend = ForegroundMap.SouthEastBend + 12,
	SouthWestBend = ForegroundMap.SouthWestBend + 12,
	NorthEastBend = ForegroundMap.NorthEastBend + 12,
	NorthWestBend = ForegroundMap.NorthWestBend + 12, 
	Empty = ForegroundMap.Interior2 + 12
};

static TileMap HitMap = new TileMap
{
	Interior1 = 1,
	Interior2 = 1,
	Interior3 = 1,
	NorthWestCorner = 1,
	NorthEdge = 1,
	NorthEastCorner = 1,
	WestEdge = 1,
	EastEdge = 1,
	SouthWestCorner = 1,
	SouthEdge = 1,
	SouthEastCorner = 1,
	NorthVertical = 1,
	MiddleVertical = 1,
	SouthVertical = 1,
	WestHorizontal = 1,
	MiddleHorizontal = 1,
	EastHorizontal = 1,
	OneByOne = 1,
	SouthEastBend = 1,
	SouthWestBend = 1,
	NorthEastBend = 1,
	NorthWestBend = 1, 
	Empty = 0
};

public delegate bool IsSolidDelegate(Bitmap map, int x, int y);

int GetTile(Bitmap map, int x, int y, bool isMainMap, bool isHitMap) 
{
	TileMap tileMap = ForegroundMap;
	IsSolidDelegate isSolid = IsForeground;
	
	if (!isMainMap) 
	{
		tileMap = BackgroundMap;
	}
	else if (isHitMap)
	{
		tileMap = HitMap;
	}
	else 
	{
		bool isForeground = IsForeground(map, x, y);
		bool isTouchingMiddleground = IsNorthSolid(map, x, y, IsMiddleground) || IsEastSolid(map, x, y, IsMiddleground) || IsSouthSolid(map, x, y, IsMiddleground) || IsWestSolid(map, x, y, IsMiddleground);
		
		if (!isForeground)
		{
			tileMap = MiddlegroundMap;
			isSolid = IsForegroundOrMiddleground;
		}
		else if (isTouchingMiddleground)
		{
			tileMap = AltForegroundMap;
		}
	}
	
	if (!isSolid(map, x, y)) return tileMap.Empty;
	
	if (!IsNorthSolid(map, x, y, isSolid) && IsEastSolid(map, x, y, isSolid) && IsSouthSolid(map, x, y, isSolid) && !IsWestSolid(map, x, y, isSolid)) return tileMap.NorthWestCorner;
	if (!IsNorthSolid(map, x, y, isSolid) && IsEastSolid(map, x, y, isSolid) && IsSouthSolid(map, x, y, isSolid) && IsWestSolid(map, x, y, isSolid)) return tileMap.NorthEdge;
	if (!IsNorthSolid(map, x, y, isSolid) && !IsEastSolid(map, x, y, isSolid) && IsSouthSolid(map, x, y, isSolid) && IsWestSolid(map, x, y, isSolid)) return tileMap.NorthEastCorner;
	if (IsNorthSolid(map, x, y, isSolid) && IsEastSolid(map, x, y, isSolid) && IsSouthSolid(map, x, y, isSolid) && !IsWestSolid(map, x, y, isSolid)) return tileMap.WestEdge;
	if (IsNorthSolid(map, x, y, isSolid) && !IsEastSolid(map, x, y, isSolid) && IsSouthSolid(map, x, y, isSolid) && IsWestSolid(map, x, y, isSolid)) return tileMap.EastEdge;
	if (IsNorthSolid(map, x, y, isSolid) && IsEastSolid(map, x, y, isSolid) && !IsSouthSolid(map, x, y, isSolid) && !IsWestSolid(map, x, y, isSolid)) return tileMap.SouthWestCorner;
	if (IsNorthSolid(map, x, y, isSolid) && IsEastSolid(map, x, y, isSolid) && !IsSouthSolid(map, x, y, isSolid) && IsWestSolid(map, x, y, isSolid)) return tileMap.SouthEdge;
	if (IsNorthSolid(map, x, y, isSolid) && !IsEastSolid(map, x, y, isSolid) && !IsSouthSolid(map, x, y, isSolid) && IsWestSolid(map, x, y, isSolid)) return tileMap.SouthEastCorner;
	if (!IsNorthSolid(map, x, y, isSolid) && !IsEastSolid(map, x, y, isSolid) && IsSouthSolid(map, x, y, isSolid) && !IsWestSolid(map, x, y, isSolid)) return tileMap.NorthVertical;
	if (IsNorthSolid(map, x, y, isSolid) && !IsEastSolid(map, x, y, isSolid) && IsSouthSolid(map, x, y, isSolid) && !IsWestSolid(map, x, y, isSolid)) return tileMap.MiddleVertical;
	if (IsNorthSolid(map, x, y, isSolid) && !IsEastSolid(map, x, y, isSolid) && !IsSouthSolid(map, x, y, isSolid) && !IsWestSolid(map, x, y, isSolid)) return tileMap.SouthVertical;
	if (!IsNorthSolid(map, x, y, isSolid) && IsEastSolid(map, x, y, isSolid) && !IsSouthSolid(map, x, y, isSolid) && !IsWestSolid(map, x, y, isSolid)) return tileMap.WestHorizontal;
	if (!IsNorthSolid(map, x, y, isSolid) && IsEastSolid(map, x, y, isSolid) && !IsSouthSolid(map, x, y, isSolid) && IsWestSolid(map, x, y, isSolid)) return tileMap.MiddleHorizontal;
	if (!IsNorthSolid(map, x, y, isSolid) && !IsEastSolid(map, x, y, isSolid) && !IsSouthSolid(map, x, y, isSolid) && IsWestSolid(map, x, y, isSolid)) return tileMap.EastHorizontal;
	if (!IsNorthSolid(map, x, y, isSolid) && !IsEastSolid(map, x, y, isSolid) && !IsSouthSolid(map, x, y, isSolid) && !IsWestSolid(map, x, y, isSolid)) return tileMap.OneByOne;
	if (IsNorthSolid(map, x, y, isSolid) && IsEastSolid(map, x, y, isSolid) && IsSouthSolid(map, x, y, isSolid) && IsWestSolid(map, x, y, isSolid)) 
	{
		if (!IsSouthEastSolid(map, x, y, isSolid)) return tileMap.SouthEastBend;
		if (!IsSouthWestSolid(map, x, y, isSolid)) return tileMap.SouthWestBend;
		if (!IsNorthEastSolid(map, x, y, isSolid)) return tileMap.NorthEastBend;
		if (!IsNorthWestSolid(map, x, y, isSolid)) return tileMap.NorthWestBend;
		
		if ((x * 3 + y * 5) % 19 == 0) return tileMap.Interior2;
		if ((x * 5 + y * 3) % 17 == 0) return tileMap.Interior3;
	}
	
	return tileMap.Interior1;
}

bool IsForeground(Bitmap map, int x, int y)
{
	if (IsOffMap(map, x, y)) return true;
	
	return map.GetPixel(x, y).R == 0;
}

bool IsMiddleground(Bitmap map, int x, int y)
{
	if (IsOffMap(map, x, y)) return false;
	
	return map.GetPixel(x, y).B == 0;
}

bool IsEmpty(Bitmap map, int x, int y) 
{
	if (IsOffMap(map, x, y)) return false;
	
	return map.GetPixel(x, y).R == 255 && map.GetPixel(x, y).G == 255 && map.GetPixel(x, y).B == 255;
}

bool IsForegroundOrMiddleground(Bitmap map, int x, int y) 
{
	return IsForeground(map, x, y) || IsMiddleground(map, x, y);
}

bool IsOffMap(Bitmap map, int x, int y)
{
	if (x < 0 || x >= map.Width) return true;
	if (y < 0 || y >= map.Height) return true;
	
	return false;
}

bool IsNorthSolid(Bitmap map, int x, int y, IsSolidDelegate IsSolid) 
{
	return IsSolid(map, x, y - 1);
}

bool IsSouthSolid(Bitmap map, int x, int y, IsSolidDelegate IsSolid) 
{
	return IsSolid(map, x, y + 1);
}

bool IsWestSolid(Bitmap map, int x, int y, IsSolidDelegate IsSolid)
{
	return IsSolid(map, x - 1, y);
}

bool IsEastSolid(Bitmap map, int x, int y, IsSolidDelegate IsSolid)
{
	return IsSolid(map, x + 1, y);
}

bool IsSouthEastSolid(Bitmap map, int x, int y, IsSolidDelegate IsSolid) 
{
	return IsSolid(map, x + 1, y + 1);
}

bool IsSouthWestSolid(Bitmap map, int x, int y, IsSolidDelegate IsSolid) 
{
	return IsSolid(map, x - 1, y + 1);
}

bool IsNorthEastSolid(Bitmap map, int x, int y, IsSolidDelegate IsSolid) 
{
	return IsSolid(map, x + 1, y - 1);
}

bool IsNorthWestSolid(Bitmap map, int x, int y, IsSolidDelegate IsSolid) 
{
	return IsSolid(map, x - 1, y - 1);
}

