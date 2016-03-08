using System.ComponentModel.DataAnnotations;
using System.Globalization;

namespace DASA_WCS.Models
{
    public class ProfileModel
    {
        public int ProfileId { get; set; }

        public string ProfileName { get; set; }

        [Required]
        [DataType(DataType.Password)]
        [Display(Name = "Password")]
        public string Password { get; set; }

        public double Temperature { get; set; }

        public string ShowerMode { get; set; }

        public int ShowerPositionX { get; set; }
        public int ShowerPositionY { get; set; }
        public int ShowerPositionZ { get; set; }
    }
}