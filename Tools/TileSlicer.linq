<Query Kind="Program">
  <Namespace>System.Drawing</Namespace>
</Query>

void Main()
{
	Bitmap destination = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\tiles-blank.png"), true);
	Bitmap source = (Bitmap)Image.FromFile(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\rocks2.png"), true);
	
	int index = 272 / 8;
	// Main 3x3 tiles
	
	for (int y = 0; y < 3; y++) 
	{
		for (int x = 0; x < 3; x++) 
		{
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
	
	// Vertical single width
	for (int y = 0; y < 3; y++) 
	{
		CopyRegionIntoImage(source, new Rectangle(3 * 16, y * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
		CopyRegionIntoImage(source, new Rectangle(3 * 16 + 8, y * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
		CopyRegionIntoImage(source, new Rectangle(3 * 16, y * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
		CopyRegionIntoImage(source, new Rectangle(3 * 16 + 8, y * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
	}
	
	// Horizontal single width
	for (int x = 0; x < 3; x++) 
	{
		CopyRegionIntoImage(source, new Rectangle(x * 16, 3 * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
		CopyRegionIntoImage(source, new Rectangle(x * 16 + 8, 3 * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
		CopyRegionIntoImage(source, new Rectangle(x * 16, 3 * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
		CopyRegionIntoImage(source, new Rectangle(x * 16 + 8, 3 * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
	}
	
	// 1x1
	CopyRegionIntoImage(source, new Rectangle(3 * 16, 3 * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
	index++;
	CopyRegionIntoImage(source, new Rectangle(3 * 16 + 8, 3 * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
	index++;
	CopyRegionIntoImage(source, new Rectangle(3 * 16, 3 * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
	index++;
	CopyRegionIntoImage(source, new Rectangle(3 * 16 + 8, 3 * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
	index++;
	
	// Inside corners
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++) 
		{
			CopyRegionIntoImage(source, new Rectangle(x * 16, 4 * 16 + y * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
			index++;
			CopyRegionIntoImage(source, new Rectangle(x * 16 + 8, 4 * 16 + y * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
			index++;
			CopyRegionIntoImage(source, new Rectangle(x * 16, 4 * 16 + y * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
			index++;
			CopyRegionIntoImage(source, new Rectangle(x * 16 + 8, 4 * 16 + y * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
			index++;
		}
	}
	
	// Alternative fills
	for (int y = 0; y < 2; y++) 
	{
		CopyRegionIntoImage(source, new Rectangle(2 * 16, 4 * 16 + y * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
		CopyRegionIntoImage(source, new Rectangle(2 * 16 + 8, 4 * 16 + y * 16, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
		CopyRegionIntoImage(source, new Rectangle(2 * 16, 4 * 16 + y * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
		CopyRegionIntoImage(source, new Rectangle(2 * 16 + 8, 4 * 16 + y * 16 + 8, 8, 8), ref destination, new Rectangle(0, index * 8, 8, 8));
		index++;
	}
	
	destination.Save(Path.Combine(Path.GetDirectoryName(Util.CurrentQueryPath), "..\\Assets\\tiles.png"));
}


public static void CopyRegionIntoImage(Bitmap srcBitmap, Rectangle srcRegion,ref Bitmap destBitmap, Rectangle destRegion)
{
    using (Graphics grD = Graphics.FromImage(destBitmap))            
    {
        grD.DrawImage(srcBitmap, destRegion, srcRegion, GraphicsUnit.Pixel);                
    }
}