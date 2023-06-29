using Laborator5.Models;
using Microsoft.AspNetCore.Mvc;

namespace Laborator5.Controllers
{
    public class ArticlesController : Controller
    {
        private AppDBContext db = new AppDBContext();

        /*

        private readonly AppDBContext db;

        public ArticlesController(AppDBContext context)
        {
            db = context;
        }

        */

        public IActionResult Index()
        {
            var articles = from article in db.Articles
                           select article;

            ViewBag.Articles = articles;

            return View();
        }

        public ActionResult Show(int id)
        {
            Article article = db.Articles.Find(id);

            ViewBag.Article = article;

            return View();
        }

        public IActionResult New()
        {
            return View();
        }

        [HttpPost]
        public IActionResult New(Article art)
        {
            try
            {
                db.Articles.Add(art);

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
            Article article = db.Articles.Find(id);

            ViewBag.Article = article;

            return View();
        }

        [HttpPost]
        public ActionResult Edit(int id, Article requestArticle)
        {
            Article article = db.Articles.Find(id);

            try
            {
                article.Title = requestArticle.Title;
                article.Content = requestArticle.Content;
                article.Date = requestArticle.Date;

                db.SaveChanges();

                return RedirectToAction("Index");
            }
            catch (Exception)
            {
                return RedirectToAction("Edit", article.ArticleID);
            }
        }

        [HttpPost]
        public ActionResult Delete(int id)
        {
            Article article = db.Articles.Find(id);

            db.Articles.Remove(article);

            db.SaveChanges();

            return RedirectToAction("Index");
        }
    }
}
