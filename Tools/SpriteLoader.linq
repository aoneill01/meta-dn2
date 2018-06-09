<Query Kind="Program">
  <Namespace>System.Drawing</Namespace>
</Query>

void Main()
{
	Bitmap character = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\character.png"), true);
	/*
	Bitmap destination = new Bitmap(character.Width, character.Height * 2);
	CopyRegionIntoImage(character, new Rectangle(0, 0, character.Width, character.Height), ref destination, new Rectangle(0, 0, character.Width, character.Height));
	character.RotateFlip(RotateFlipType.RotateNoneFlipX);
	CopyRegionIntoImage(character, new Rectangle(0, 0, character.Width, character.Height), ref destination, new Rectangle(0, character.Height, character.Width, character.Height));
	
	destination.Dump();
	*/
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

public static void CopyRegionIntoImage(Bitmap srcBitmap, Rectangle srcRegion,ref Bitmap destBitmap, Rectangle destRegion)
{
    using (Graphics grD = Graphics.FromImage(destBitmap))            
    {
        grD.DrawImage(srcBitmap, destRegion, srcRegion, GraphicsUnit.Pixel);                
    }
}

int ColorToRgb565(Color color) 
{
	if (color.A != 255) return 0xFC << 3;
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