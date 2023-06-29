using System.ComponentModel.DataAnnotations;

namespace Modeltest2021.Models
{
    public class Brand
    {
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Denumirea brandului este obligatorie")]
        public string Nume { get; set; }

        public virtual ICollection<GiftCard>? GiftCards { get; set; }
    }
}
