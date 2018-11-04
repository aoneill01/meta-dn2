<Query Kind="Program">
  <Namespace>System.Drawing</Namespace>
  <Namespace>System.IO</Namespace>
  <Namespace>System.IO.Ports</Namespace>
</Query>

void Main()
{
	SerialPort serialPort = new SerialPort("COM4", 9600);
	Bitmap frame = null;
	string path = @"E:\VirtualBox\Shared\dn_game\frames";
	int frameCount = 0;
	
	try 
	{
		serialPort.Open();
		serialPort.Write(new byte[] { 1 }, 0, 1);
		
		while (true) 
		{
			if (serialPort.ReadByte() == 's' && serialPort.ReadByte() == 't' && serialPort.ReadByte() == 'a' &&
				serialPort.ReadByte() == 'r' && serialPort.ReadByte() == 't')
			{
				serialPort.Write(new byte[] { 1 }, 0, 1);
				int x = serialPort.ReadByte();
				int y = serialPort.ReadByte();
				int w = serialPort.ReadByte();
				int h = serialPort.ReadByte();
				int xInit = x;
				int yInit = y;
				
				if (y == 0)
				{
					if (frame != null)
					{
						// frame.Dump();
						frame.Save(Path.Combine(path, $"frame{frameCount.ToString().PadLeft(4, '0')}.png"), System.Drawing.Imaging.ImageFormat.Png);
					}
					frame = new Bitmap(160, 128);
					frameCount++;
					Console.WriteLine(frameCount);
				}
				
				// Console.WriteLine($"x: {x} y: {y} w: {w} h: {h}");
				
				if (frame == null) continue;
				
				while (y < yInit + h) {
					while (x < xInit + w) {
						frame.SetPixel(x, y, Rgb565ToColor((serialPort.ReadByte() << 8) | serialPort.ReadByte()));
						x++;
					}
					x -= w;
					y++;
				}
			}
		}
		
		serialPort.Close();
	}
	catch (IOException e)
	{
		Console.WriteLine(e);
	}
}

// Define other methods and classes here
Color Rgb565ToColor(int value) 
{
	int r = (value & 0b1111100000000000) >> 8;
	int g = (value & 0b0000011111100000) >> 3;
	int b = (value & 0b0000000000011111) << 3;
	return Color.FromArgb(r, g, b);
}