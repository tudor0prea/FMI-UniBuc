using Microsoft.EntityFrameworkCore;

namespace Modeltest2021.Models
{
    public class AppDBContext : DbContext
    {
        // constructorul contextului bazei de date
        public AppDBContext(DbContextOptions<AppDBContext> options) : base(options) { } 
        
        public DbSet<GiftCard> GiftCards { get; set; }
        public DbSet<Brand> Brands { get; set; }
    }
}
