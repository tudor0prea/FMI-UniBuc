using System.ComponentModel.DataAnnotations;

namespace ModelMare.Models
{
    public class Category
    {
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Numele este obligatoriu")]
        public string Nume { get; set; }

        public ICollection<Product>? Products { get; set; }
    }
}
