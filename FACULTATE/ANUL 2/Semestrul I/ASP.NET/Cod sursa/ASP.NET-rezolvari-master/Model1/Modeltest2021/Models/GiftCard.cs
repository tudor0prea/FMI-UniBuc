using Microsoft.AspNetCore.Mvc.Rendering;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace Modeltest2021.Models
{
    public class GiftCard
    {
        [Key]
        public int Id { get; set; }

        [Required(ErrorMessage = "Denumirea cardului este obligatorie")]
        public string Denumire { get; set; }

        [Required(ErrorMessage = "Descrierea cardului este obligatorie")]
        public string Descriere { get; set; }

        [Required(ErrorMessage = " Data expirarii este obligatorie")]
        [DataType(DataType.DateTime)]
        [DisplayFormat(ApplyFormatInEditMode = true, DataFormatString = "{0:dd/MM/yyyy}")]
        public DateTime? DataExp { get; set; }

        [Required(ErrorMessage = "Procentul este obligatoriu")]
        [Range(1, 100, ErrorMessage = "Procentul trebuie sa fie cuprins intre 1 si 100")]
        public int Procent { get; set; }

        [Required(ErrorMessage = "Brandul trebuie selectat")]
        public int? BrandId { get; set; }

        public virtual Brand? Brand { get; set; }

        [NotMapped]
        public IEnumerable<SelectListItem>? Brands { get; set; }
    }
}
