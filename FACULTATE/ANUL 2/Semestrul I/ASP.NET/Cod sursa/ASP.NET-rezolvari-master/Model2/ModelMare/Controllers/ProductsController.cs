using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using ModelMare.Models;
using System.ComponentModel.DataAnnotations.Schema;

namespace ModelMare.Controllers
{
    public class ProductsController : Controller
    {
        private readonly AppDbContext db;
        public ProductsController(AppDbContext context)
        {
            db = context;
        }

        public IActionResult Index()
        {
            var products = db.Products.Include("Category");
            // afisare paginata
            int _perPage = 3;

            int totalItems = products.Count();

            var currentPage = Convert.ToInt32(HttpContext.Request.Query["page"]);

            int offset = 0;
            if (!currentPage.Equals(0))
            {
                offset = (currentPage - 1) * _perPage;
            }

            var paginatedProducts = products.Skip(offset).Take(_perPage);

            ViewBag.lastPage = Math.Ceiling((float)totalItems / (float)_perPage);
            ViewBag.products = paginatedProducts;

            if(TempData.ContainsKey("message"))
                ViewBag.message = TempData["message"];

            return View();
        }

        public IActionResult New()
        {
            Product product = new Product();
            product.Categories = GetAllCategories();

            return View(product);
        }
        [HttpPost]
        public IActionResult New(Product requestProduct)
        {
            if (ModelState.IsValid)
            {
                db.Products.Add(requestProduct);
                db.SaveChanges();

                TempData["message"] = "Produsul a fost adaugat";
                return RedirectToAction("Index");
            }
            else
            {
                requestProduct.Categories = GetAllCategories();
                return View(requestProduct);
            }
        }

        [NonAction]
        public IEnumerable<SelectListItem> GetAllCategories()
        {
            var selectList = new List<SelectListItem>();
            var categories = db.Categories;

            foreach (var category in categories)
                selectList.Add(new SelectListItem
                {
                    Value = category.Id.ToString(),
                    Text = category.Nume.ToString()
                });

            return selectList;
        }
    }
}
