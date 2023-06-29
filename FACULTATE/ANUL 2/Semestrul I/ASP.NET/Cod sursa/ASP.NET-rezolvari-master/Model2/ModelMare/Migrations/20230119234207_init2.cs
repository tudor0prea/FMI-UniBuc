using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace ModelMare.Migrations
{
    /// <inheritdoc />
    public partial class init2 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.RenameColumn(
                name: "Title",
                table: "Products",
                newName: "Denumire");

            migrationBuilder.RenameColumn(
                name: "Content",
                table: "Products",
                newName: "Descriere");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.RenameColumn(
                name: "Descriere",
                table: "Products",
                newName: "Content");

            migrationBuilder.RenameColumn(
                name: "Denumire",
                table: "Products",
                newName: "Title");
        }
    }
}
