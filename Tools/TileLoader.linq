<Query Kind="Program">
  <Namespace>System.Drawing</Namespace>
</Query>

void Main()
{
	Bitmap tiles = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\sample-tiles.png"), true);
	
	tiles.Dump();
	
	string result = "";
	
	for (int y = 0; y < tiles.Height; y++)
	{
		for (int x = 0; x < tiles.Width; x += 2) 
		{
			string firstHex = ToZeroPaddedHex4(SwapEndian16(ColorToRgb565(tiles.GetPixel(x, y))));
			string secondHex = ToZeroPaddedHex4(SwapEndian16(ColorToRgb565(tiles.GetPixel(x + 1, y))));
			
			if (!string.IsNullOrEmpty(result)) 
			{
				result += ", ";
			}
			
			result += "0x" + secondHex + firstHex;
		}
	}
	
	result = "const uint32_t sample_tilesData[] = { " + result + " };";
	result.Dump();
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