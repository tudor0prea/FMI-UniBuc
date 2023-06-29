using Laborator5.Models;
using Microsoft.AspNetCore.Mvc;

namespace Laborator5.Controllers
{
    public class CategoriesController : Controller
    {

        private AppDBContext db = new AppDBContext();

        /*
        private readonly AppDBContext db;

        public CategoriesController(AppDBContext context)
        {
            db = context;
        }

        */

        public IActionResult Index()
        {
            var categories = from categ in db.Categories
                             select categ;

            ViewBag.Categories = categories;

            return View();
        }

        public ActionResult Show(int id)
        {
            Category categ = db.Categories.Find(id);

            ViewBag.Category = categ;

            return View();
        }

        public IActionResult New()
        {
            return View();
        }

        [HttpPost]
        public IActionResult New(Category categ)
        {
            try
            {
                db.Categories.Add(categ);

                db.SaveChanges();

                return RedirectToAction("Index");
            }
            catch (Exception)
            {
                return View();
            }

        }

        public IActionResult Edit(int id)
        {
            Category categ = db.Categories.Find(id);

            ViewBag.Categories = categ;

            return View();
        }

        [HttpPost]
        public ActionResult Edit(int id, Category requestCateg)
        {
            Category categ = db.Categories.Find(id);

            try
            {
                categ.CategoryName = requestCateg.CategoryName;

                db.SaveChanges();

                return RedirectToAction("Index");
            }
            catch (Exception)
            {
                return RedirectToAction("Edit", categ.CategoryId);
            }
        }

        [HttpPost]
        public ActionResult Delete(int id)
        {
            Category categ = db.Categories.Find(id);

            db.Categories.Remove(categ);

            db.SaveChanges();

            return RedirectToAction("Index");
        }
    }
}
