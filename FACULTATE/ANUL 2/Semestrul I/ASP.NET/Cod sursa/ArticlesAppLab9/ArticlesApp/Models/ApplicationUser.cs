using Microsoft.AspNetCore.Identity;


// PASUL 1 - useri si roluri 
namespace ArticlesApp.Models 
{
    public class ApplicationUser : IdentityUser
    {
        public virtual ICollection<Comment>? Comments { get; set; }

        public virtual ICollection<Article>? Articles { get; set; }
    }
}
