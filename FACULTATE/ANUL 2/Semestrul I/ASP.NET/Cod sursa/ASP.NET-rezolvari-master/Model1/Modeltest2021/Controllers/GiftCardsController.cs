using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using Modeltest2021.Models;
using NuGet.Versioning;
using static Microsoft.EntityFrameworkCore.DbLoggerCategory;

namespace Modeltest2021.Controllers
{
    public class GiftCardsController : Controller
    {
        private readonly AppDBContext db;
        public GiftCardsController(AppDBContext context)
        {
            db = context;
        }

        public IActionResult Index()
        {
            // afisarea cardurilor cadou + brand
            var cards = db.GiftCards.Include("Brand");

            ViewBag.cards = cards;

            if(TempData.ContainsKey("message"))
                ViewBag.message = TempData["message"];

            return View();
        }
        public IActionResult Show(int? id)
        {
            var card = db.GiftCards.Include("Brand").Where(c => c.Id == (int)id).First();

            if (TempData.ContainsKey("message"))
                ViewBag.message = TempData["message"];

            return View(card);
        }
        
        public IActionResult New()
        {
            GiftCard card = new GiftCard();
            card.Brands = GetAllBrands();
            return View(card);
        }
        [HttpPost]
        public IActionResult New(GiftCard requestCard)
        {
            if (ModelState.IsValid)
            {
                db.GiftCards.Add(requestCard);
                db.SaveChanges();
                TempData["message"] = "Cardul a fost adaugat";
                return RedirectToAction("Index");
            }
            else
            {
                requestCard.Brands = GetAllBrands();
                return View(requestCard);
            }
        }

        public IActionResult Edit(int? id)
        {
            var card = db.GiftCards.Include("Brand").Where(c => c.Id == (int)id).First();
            
            card.Brands = GetAllBrands();
            return View(card);
        }
        [HttpPost]
        public IActionResult Edit(int? id, GiftCard requestCard)
        {
            var card = db.GiftCards.Include("Brand").Where(c => c.Id == (int)id).First();
            if (ModelState.IsValid)
            {
                card.Denumire = requestCard.Denumire;
                card.Descriere = requestCard.Descriere;
                card.DataExp = requestCard.DataExp;
                card.Procent = requestCard.Procent;

                db.SaveChanges();
                TempData["message"] = "Cardul a fost modificat";
                return Redirect("/GiftCards/Show/" + (int) id);
            }
            else
            {
                requestCard.Brands = GetAllBrands();
                requestCard.DataExp = card.DataExp;

                return View(requestCard);
            }
        }
        public IActionResult Delete(int? id)
        {
            var card = db.GiftCards.Include("Brand").Where(c => c.Id == (int)id).First();
            db.GiftCards.Remove(card);
            db.SaveChanges();

            TempData["message"] = "Cardul a fost sters";

            return RedirectToAction("Index");
        }

        public IActionResult Search()
        {
            var cards = db.GiftCards.Include("Brand");
            var search = "";
            if (Convert.ToString(HttpContext.Request.Query["search"]) != null)
            {
                search = Convert.ToString(HttpContext.Request.Query["search"]).Trim(); // eliminam spatiile libere 
                List<int> cardIds = db.GiftCards.Where
                                        (
                                         at => at.Denumire.Contains(search)
                                         || at.Descriere.Contains(search)
                                        ).Select(a => a.Id).ToList();

                cards = db.GiftCards.Include("Brand")
                          .Where(c => cardIds.Contains(c.Id)
                                      && c.DataExp.Value.Day <= DateTime.Now.Day + 5 && c.DataExp.Value.Month == DateTime.Now.Month && c.DataExp.Value.Year == DateTime.Now.Year
                                      && c.Procent <= 30)
                          .OrderByDescending(c => c.DataExp);
            }
            ViewBag.SearchString = search;
            ViewBag.Cards = cards;
            return View();
        }

        [NonAction]
        public IEnumerable<SelectListItem> GetAllBrands()
        {
            // generam o lista de tipul SelectListItem fara elemente
            var selectList = new List<SelectListItem>();

            var brands = from brand in db.Brands
                         select brand;

            // iteram prin categorii
            foreach (var brand in brands)
                selectList.Add(new SelectListItem
                {
                    Value = brand.Id.ToString(),
                    Text = brand.Nume.ToString()
                });

            return selectList;
         }
           
            
        
    }
}
