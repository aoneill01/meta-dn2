<Query Kind="Program">
  <Namespace>System.Drawing</Namespace>
</Query>

void Main()
{
	Bitmap character = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\character.png"), true);
	
	character.Dump();
	
	string result = "";
	
	for (int y = 0; y < character.Height; y++)
	{
		for (int x = 0; x < character.Width; x ++) 
		{
			string hex = ToZeroPaddedHex4(SwapEndian16(ColorToRgb565(character.GetPixel(x, y))));
			
			if (!string.IsNullOrEmpty(result)) 
			{
				result += ", ";
			}
			
			result += "0x" + hex;
		}
	}
	
	result = "const uint16_t characterData[] = { " + result + " };";
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