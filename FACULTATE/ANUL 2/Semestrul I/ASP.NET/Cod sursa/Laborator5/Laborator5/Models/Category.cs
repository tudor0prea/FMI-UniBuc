using System.ComponentModel.DataAnnotations;

namespace Laborator5.Models
{
    public class Category
    {
        [Key]
        public int CategoryId { get; set; }
        public string CategoryName { get; set; }
    }
}
