
import os
from decimal import Decimal, InvalidOperation

import mysql.connector
from flask import Flask, request, redirect, url_for, render_template_string, flash

app = Flask(__name__)
app.secret_key = os.environ.get("FLASK_SECRET_KEY", "change-this-secret")


def get_connection():
    return mysql.connector.connect(
        host=os.environ["DB_HOST"],
        database=os.environ["DB_NAME"],
        user=os.environ["DB_USER"],
        password=os.environ["DB_PASSWORD"]
    )


def get_inventory():
    connection = get_connection()
    cursor = connection.cursor(dictionary=True)

    cursor.execute("""
        SELECT i.sku, i.name, i.description, i.baseCost,
               i.discountPercent, i.location, i.warehouse, i.`count`,
               p.image_url
        FROM inventory i
        LEFT JOIN part_images p ON i.sku = p.sku
        ORDER BY i.sku
    """)

    items = cursor.fetchall()
    cursor.close()
    connection.close()
    return items


@app.route("/")
def home():
    items = get_inventory()

    warehouses = sorted({
        item["warehouse"] for item in items if item["warehouse"]
    })

    locations = sorted({
        item["location"] for item in items if item["location"]
    })

    return render_template_string("""
<!DOCTYPE html>
<html>
<head>
    <title>Auto Parts Inventory</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <style>
        * { box-sizing: border-box; }

        body {
            margin: 0;
            font-family: "Segoe UI", Arial, sans-serif;
            background: #e9edf2;
            color: #202b38;
        }

        header {
            background: #172332;
            color: white;
            padding: 28px 35px;
            border-bottom: 5px solid #f47721;
        }

        header h1 {
            margin: 0;
            font-size: 30px;
            letter-spacing: 1px;
            text-transform: uppercase;
        }

        header p {
            color: #aab7c6;
            margin: 8px 0 0;
            letter-spacing: 2px;
            font-size: 12px;
        }

        main {
            max-width: 1600px;
            margin: auto;
            padding: 28px;
        }

        .panel {
            background: white;
            border-radius: 8px;
            padding: 24px;
            margin-bottom: 24px;
            border: 1px solid #d6dde6;
            box-shadow: 0 4px 12px #17233212;
        }

        .panel h2 {
            text-transform: uppercase;
            font-size: 19px;
            letter-spacing: 1px;
            border-left: 4px solid #f47721;
            padding-left: 12px;
        }

        input, select {
            padding: 12px;
            border: 1px solid #cbd4df;
            border-radius: 5px;
            background: #f9fafc;
        }

        button {
            padding: 11px 16px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-weight: 600;
        }

        .primary {
            background: #f47721;
            color: white;
        }

        .danger {
            background: #fbe4e4;
            color: #a52b2b;
        }

        .muted {
            background: #e5eaf0;
            color: #34445c;
        }

        .filters {
            display: flex;
            gap: 12px;
            flex-wrap: wrap;
            margin: 18px 0;
        }

        input[type="search"] {
            flex: 1;
            min-width: 220px;
        }

        .table-wrap { overflow-x: auto; }

        table {
            width: 100%;
            border-collapse: collapse;
            min-width: 1100px;
        }

        th {
            background: #263748;
            color: white;
            text-align: left;
            padding: 15px;
            border-bottom: 3px solid #f47721;
            text-transform: uppercase;
            font-size: 12px;
            letter-spacing: 1px;
        }

        td {
            padding: 14px;
            border-bottom: 1px solid #e2e7ed;
        }

        tbody tr:nth-child(even) { background: #f5f7fa; }
        tbody tr:hover { background: #fff2e7; }

        .part-image {
            width: 65px;
            height: 65px;
            object-fit: contain;
            background: white;
            border: 1px solid #d8dee7;
            border-radius: 5px;
            padding: 4px;
        }

        .badge {
            padding: 6px 10px;
            border-radius: 4px;
            font-size: 12px;
            font-weight: bold;
        }

        .in-stock {
            background: #e1f3e8;
            color: #207443;
        }

        .out-stock {
            background: #fbe4e4;
            color: #a52b2b;
        }

        .add-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(180px, 1fr));
            gap: 12px;
        }

        .add-grid input { width: 100%; }

        .message {
            background: #e1f3e8;
            padding: 12px;
            border-radius: 5px;
        }

        @media (max-width: 600px) {
            main { padding: 14px; }
            header { padding: 22px 16px; }
        }
    </style>
</head>

<body>
<header>
    <h1>Auto Parts Inventory</h1>
    <p>WAREHOUSE MANAGEMENT SYSTEM</p>
</header>

<main>
    {% for message in get_flashed_messages() %}
        <div class="message">{{ message }}</div>
    {% endfor %}

    <section class="panel">
        <h2>Inventory Catalog</h2>

        <div class="filters">
            <input type="search" id="search"
                   placeholder="Search SKU, name, or description...">

            <select id="warehouseFilter">
                <option value="">All warehouses</option>
                {% for warehouse in warehouses %}
                    <option value="{{ warehouse }}">{{ warehouse }}</option>
                {% endfor %}
            </select>

            <select id="locationFilter">
                <option value="">All locations</option>
                {% for location in locations %}
                    <option value="{{ location }}">{{ location }}</option>
                {% endfor %}
            </select>

            <button class="muted" onclick="resetFilters()">Reset</button>
        </div>

        <p id="resultCount">{{ items|length }} records</p>

        <div class="table-wrap">
        <table id="inventoryTable">
            <thead>
                <tr>
                    <th>Image</th>
                    <th>SKU</th>
                    <th>Name</th>
                    <th>Description</th>
                    <th>Base Cost</th>
                    <th>Location</th>
                    <th>Warehouse</th>
                    <th>Quantity</th>
                    <th>Stock Status</th>
                    <th>Action</th>
                </tr>
            </thead>
            <tbody>
            {% for item in items %}
                <tr>
                    <td>
                        {% if item.image_url %}
                            <img class="part-image"
                                 src="{{ item.image_url }}"
                                 alt="{{ item.name }}"
                                 loading="lazy">
                        {% else %}
                            <span>No image</span>
                        {% endif %}
                    </td>
                    <td>{{ item.sku }}</td>
                    <td>{{ item.name }}</td>
                    <td>{{ item.description or "" }}</td>
                    <td>${{ "%.2f"|format(item.baseCost or 0) }}</td>
                    <td>{{ item.location or "" }}</td>
                    <td>{{ item.warehouse or "" }}</td>
                    <td>{{ item.count or 0 }}</td>
                    <td>
                        {% if item.count and item.count > 0 %}
                            <span class="badge in-stock">IN STOCK</span>
                        {% else %}
                            <span class="badge out-stock">OUT OF STOCK</span>
                        {% endif %}
                    </td>
                    <td>
                        <form method="POST" action="/delete/{{ item.sku }}"
                              onsubmit="return confirm('Delete SKU {{ item.sku }}?');">
                            <button class="danger" type="submit">Delete</button>
                        </form>
                    </td>
                </tr>
            {% endfor %}
            </tbody>
        </table>
        </div>
    </section>

    <section class="panel">
        <h2>Add Inventory Item</h2>

        <form method="POST" action="/add">
            <div class="add-grid">
                <input name="sku" placeholder="SKU (required)" required maxlength="50">
                <input name="name" placeholder="Item name (required)" required maxlength="100">
                <input name="baseCost" type="number" step="0.01"
                       min="0" placeholder="Base cost" required>
                <input name="discountPercent" type="number" step="0.000001"
                       min="0" max="100" placeholder="Discount %">
                <input name="description" placeholder="Description">
                <input name="location" placeholder="Location" maxlength="50">
                <input name="warehouse" placeholder="Warehouse">
                <input name="count" type="number" min="0" placeholder="Quantity">
                <input name="image_url" type="url"
                       placeholder="Image URL (optional)">
            </div>
            <br>
            <button class="primary" type="submit">Add Item</button>
        </form>
    </section>
</main>

<script>
    const search = document.getElementById("search");
    const warehouseFilter = document.getElementById("warehouseFilter");
    const locationFilter = document.getElementById("locationFilter");
    const rows = [...document.querySelectorAll("#inventoryTable tbody tr")];
    const resultCount = document.getElementById("resultCount");

    function filterRows() {
        const query = search.value.toLowerCase();
        const warehouse = warehouseFilter.value.toLowerCase();
        const location = locationFilter.value.toLowerCase();
        let visible = 0;

        rows.forEach(row => {
            const text = row.innerText.toLowerCase();
            const rowWarehouse = row.cells[6].innerText.toLowerCase();
            const rowLocation = row.cells[5].innerText.toLowerCase();

            const matches = text.includes(query)
                && (!warehouse || rowWarehouse === warehouse)
                && (!location || rowLocation === location);

            row.style.display = matches ? "" : "none";
            if (matches) visible++;
        });

        resultCount.textContent = visible + " records shown";
    }

    function resetFilters() {
        search.value = "";
        warehouseFilter.value = "";
        locationFilter.value = "";
        filterRows();
    }

    search.addEventListener("input", filterRows);
    warehouseFilter.addEventListener("change", filterRows);
    locationFilter.addEventListener("change", filterRows);
</script>
</body>
</html>
""", items=items, warehouses=warehouses, locations=locations)


@app.route("/add", methods=["POST"])
def add_item():
    sku = request.form.get("sku", "").strip()
    name = request.form.get("name", "").strip()

    if not sku or not name:
        flash("SKU and item name are required.")
        return redirect(url_for("home"))

    try:
        base_cost = Decimal(request.form.get("baseCost", ""))
        discount = Decimal(request.form.get("discountPercent") or "0")
        quantity_text = request.form.get("count", "").strip()
        quantity = int(quantity_text) if quantity_text else None

        if base_cost < 0 or discount < 0 or discount > 100:
            raise ValueError

        if quantity is not None and quantity < 0:
            raise ValueError

    except (InvalidOperation, ValueError):
        flash("Enter valid cost, discount (0-100), and quantity.")
        return redirect(url_for("home"))

    image_url = request.form.get("image_url", "").strip()

    connection = get_connection()
    cursor = connection.cursor()

    try:
        connection.start_transaction()

        cursor.execute("""
            INSERT INTO inventory
            (sku, name, description, baseCost, discountPercent,
             location, warehouse, `count`)
            VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
        """, (
            sku, name,
            request.form.get("description") or None,
            base_cost, discount,
            request.form.get("location") or None,
            request.form.get("warehouse") or None,
            quantity
        ))

        if image_url:
            cursor.execute("""
                INSERT INTO part_images (sku, image_url)
                VALUES (%s, %s)
            """, (sku, image_url))

        connection.commit()
        flash("Inventory item added.")

    except mysql.connector.Error:
        connection.rollback()
        flash("Could not add item. Check whether the SKU already exists.")

    finally:
        cursor.close()
        connection.close()

    return redirect(url_for("home"))


@app.route("/delete/<sku>", methods=["POST"])
def delete_item(sku):
    connection = get_connection()
    cursor = connection.cursor()

    try:
        connection.start_transaction()

        cursor.execute("DELETE FROM part_images WHERE sku = %s", (sku,))
        cursor.execute("DELETE FROM inventory WHERE sku = %s", (sku,))

        connection.commit()
        flash("Item deleted.")

    except mysql.connector.Error:
        connection.rollback()
        flash("Could not delete item.")

    finally:
        cursor.close()
        connection.close()

    return redirect(url_for("home"))


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)

