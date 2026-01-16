using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BIMManager
{

    [StructLayout(LayoutKind.Sequential)]
    public struct PartParams
    {
        public double Length;
        public double Width;
        public double Height;
        public double DraftAngle;
        public double FilletRadius;
    }

    public class CreoData
    {
        public double Length { get; set; }
        public double Width { get; set; }
        public double Height { get; set; }
        public double DraftAngle { get; set; }
        public double FilletRadius { get; set; }
    }
}
