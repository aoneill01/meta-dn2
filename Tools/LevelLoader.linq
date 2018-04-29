<Query Kind="Program">
  <Namespace>System.Drawing</Namespace>
</Query>

void Main()
{
	Bitmap map = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\level.png"), true);
	
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
			
			string left = "30";
			string right = "31";
			if (!IsSolid(map, x, y)) {
				tmp += "0, 0";
			}
			else {
				if (!IsSolid(map, x, y - 1) && IsSolid(map, x - 1, y)) left = "9";
				else if (!IsSolid(map, x, y - 1) && !IsSolid(map, x - 1, y)) left = "1";
				else if (IsSolid(map, x, y - 1) && !IsSolid(map, x - 1, y)) left = "3";
				
				if (!IsSolid(map, x, y - 1) && IsSolid(map, x + 1, y)) right = "10";
				else if (!IsSolid(map, x, y - 1) && !IsSolid(map, x + 1, y)) right = "5";
				else if (IsSolid(map, x, y - 1) && !IsSolid(map, x + 1, y)) right = "7";
				
				tmp += left + ", " + right;
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
			
			string left = "32";
			string right = "33";
			if (!IsSolid(map, x, y)) {
				tmp += "0, 0";
			}
			else {
				if (!IsSolid(map, x, y + 1) && IsSolid(map, x - 1, y)) left = "11";
				else if (!IsSolid(map, x, y + 1) && !IsSolid(map, x - 1, y)) left = "4";
				else if (IsSolid(map, x, y + 1) && !IsSolid(map, x - 1, y)) left = "2";
				
				if (!IsSolid(map, x, y + 1) && IsSolid(map, x + 1, y)) right = "12";
				else if (!IsSolid(map, x, y + 1) && !IsSolid(map, x + 1, y)) right = "8";
				else if (IsSolid(map, x, y + 1) && !IsSolid(map, x + 1, y)) right = "6";
				
				tmp += left + ", " + right;
			}
		
		}
		result += "{" + tmp + "},\n";
	}
	
	result = "const uint16_t layer1[LAYER_HEIGHT][LAYER_WIDTH] = {\n" + result + "};";
	result.Dump();
}

bool IsSolid(Bitmap map, int x, int y) {
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