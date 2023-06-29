using Microsoft.AspNetCore.Mvc.Rendering;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ModelMare.Models
{
    public class Product
    {
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Titlul este obligatoriu")]
        [MaxLength(100, ErrorMessage = "Titlul trebuie sa contina maxim 100 caractere")]
        public string Denumire { get; set; }

        [Required(ErrorMessage = "Continutul este obligatoriu")]
        [MinLength(5, ErrorMessage = ">5")]
        public string Descriere { get; set; }

        [Required(ErrorMessage = "Data expirarii este obligatorie")]
        [DataType(DataType.DateTime)]
        [DisplayFormat(DataFormatString = "{0:dd/MM/yyyy}", ApplyFormatInEditMode = true)]
        public DateTime? DateExp { get; set; }

        [Required(ErrorMessage = "Categoria este obligatorie")]
        public int? CategoryId { get; set; }

        public virtual Category? Category { get; set; }

        [NotMapped]
        public IEnumerable<SelectListItem>? Categories { get; set; }

    }
}
