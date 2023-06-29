using Microsoft.EntityFrameworkCore;

namespace Laborator5.Models
{
    public class AppDBContext : DbContext
    {

        public AppDBContext() : base()
        {
        }

        /*
        public AppDBContext(DbContextOptions<AppDBContext> options)
            : base(options)
        {
        }

        */

        protected override void OnConfiguring(DbContextOptionsBuilder options)
        {
            options.UseSqlServer(@"Laborator5test");
        }

        public DbSet<Article> Articles { get; set; }
        public DbSet<Category> Categories { get; set; }

    }
}
