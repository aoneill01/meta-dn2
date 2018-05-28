<Query Kind="Program">
  <Namespace>System.Drawing</Namespace>
</Query>

void Main()
{
	Bitmap destination = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\tiles-blank.png"), true);
	Bitmap source = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\tiles.png"), true);
	
	int index = 0;
	
	for (int y = 0; y < 16; y++) 
	{
		for (int x = 0; x < 16; x++) {
			CopyRegionIntoImage(source, new Rectangle(x * 16, y * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
			index++;
			CopyRegionIntoImage(source, new Rectangle(x * 16 + 8, y * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
			index++;
			CopyRegionIntoImage(source, new Rectangle(x * 16, y * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
			index++;
			CopyRegionIntoImage(source, new Rectangle(x * 16 + 8, y * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
			index++;
		}
	}
	
	destination.Save(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\tiles3.png"));
	
	GetCode();
}


public static void CopyRegionIntoImage(Bitmap srcBitmap, Rectangle srcRegion,ref Bitmap destBitmap, Rectangle destRegion)
{
    using (Graphics grD = Graphics.FromImage(destBitmap))            
    {
        grD.DrawImage(srcBitmap, destRegion, srcRegion, GraphicsUnit.Pixel);                
    }
}


void GetCode()
{
	Bitmap tiles = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\tiles3.png"), true);
	
	// tiles.Dump();
	
	string result = "";
	
	for (int y = 0; y < tiles.Height; y++)
	{
		if ((y % (16*16)) == 0 && y != 0) result += "\n";
		
		for (int x = 0; x < tiles.Width; x ++) 
		{
			string hex = ToZeroPaddedHex4(SwapEndian16(ColorToRgb565(tiles.GetPixel(x, y))));
			
			if (!string.IsNullOrEmpty(result)) 
			{
				result += ", ";
			}
			
			result += "0x" + hex;
		}
	}
	
	result = "const uint16_t sample_tilesData[] = { " + result + " };";
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